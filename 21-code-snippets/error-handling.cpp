#include <iostream>
#include <pqxx/pqxx>
#include <thread>
#include <chrono>

void execute_with_retry(pqxx::connection& conn, const std::string& sql, int max_retries = 3) {
    for (int attempt = 1; attempt <= max_retries; ++attempt) {
        try {
            pqxx::work txn{conn};
            txn.exec(sql);
            txn.commit();
            return;  // success
        } catch (pqxx::broken_connection const& e) {
            std::cerr << "Connection lost: " << e.what() << "\n";
            if (attempt == max_retries) throw;
            std::cerr << "Retrying in 1 second...\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
            // In a real app you'd reconnect or repair the connection object.
        } catch (pqxx::sql_error const& e) {
            std::cerr << "SQL error: " << e.what() << "\n";
            std::cerr << "Query: " << e.query() << "\n";
            // SQL errors are not retried automatically
            throw;
        } catch (std::exception const& e) {
            std::cerr << "Unexpected error: " << e.what() << "\n";
            throw;
        }
    }
}

int main(int argc, char* argv[]) {
    try {
        std::string conn_str = (argc > 1) ? argv[1] : "dbname=postgres";
        pqxx::connection conn{conn_str};

        // Example of a statement that will fail
        std::string bad_sql = "SELECT * FROM non_existent_table";

        execute_with_retry(conn, bad_sql);

    } catch (std::exception const& e) {
        std::cerr << "Fatal: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
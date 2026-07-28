#include <iostream>
#include <pqxx/pqxx>

int main(int argc, char* argv[]) {
    try {
        std::string conn_str = (argc > 1) ? argv[1] : "dbname=postgres";
        pqxx::connection conn{conn_str};

        // Create a temporary table for demonstration
        pqxx::work txn{conn};
        txn.exec("CREATE TEMP TABLE IF NOT EXISTS demo (id SERIAL PRIMARY KEY, name TEXT)");
        txn.commit();

        // Prepare a statement (connection-scoped)
        conn.prepare("insert_name", "INSERT INTO demo (name) VALUES ($1) RETURNING id");

        // Start a new transaction to execute the prepared statement
        pqxx::work insert_txn{conn};

        // Execute with a parameter
        pqxx::result res = insert_txn.exec_prepared("insert_name", "Alice");

        // Retrieve the generated id
        if (!res.empty())
            std::cout << "Inserted row with id = " << res[0][0].as<int>() << "\n";

        insert_txn.commit();

        // Verify by reading all rows
        pqxx::nontransaction read_txn{conn};
        pqxx::result all_rows = read_txn.exec("SELECT * FROM demo");
        for (auto const& row : all_rows)
            std::cout << row[0].as<int>() << " | " << row[1].c_str() << "\n";

        // Cleanup: unprepare (optional, connection close frees it)
        conn.unprepare("insert_name");

    } catch (std::exception const& e) {
        std::cerr << "ERROR: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
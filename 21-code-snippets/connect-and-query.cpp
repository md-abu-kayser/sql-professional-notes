#include <iostream>
#include <pqxx/pqxx>

int main(int argc, char* argv[]) {
    try {
        // Build connection string from command line or use default
        std::string conn_str = (argc > 1) ? argv[1] : "dbname=postgres";
        pqxx::connection conn{conn_str};

        // Create a non-transactional query (auto-commit)
        pqxx::nontransaction txn{conn};

        // Execute a query
        pqxx::result res = txn.exec(
            "SELECT schemaname, tablename FROM pg_tables WHERE tableowner = current_user LIMIT 10");

        // Print column headers
        for (int i = 0; i < res.columns(); ++i)
            std::cout << res.column_name(i) << "\t";
        std::cout << "\n" << std::string(40, '-') << "\n";

        // Iterate rows
        for (auto const& row : res) {
            for (auto const& field : row)
                std::cout << field.c_str() << "\t";
            std::cout << "\n";
        }

        // txn commits automatically on destruction (RAII)
    } catch (std::exception const& e) {
        std::cerr << "ERROR: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
#include <iostream>
#include <pqxx/pqxx>

int main(int argc, char* argv[]) {
    try {
        std::string conn_str = (argc > 1) ? argv[1] : "dbname=postgres";
        pqxx::connection conn{conn_str};

        // Create a simple accounts table
        pqxx::work setup{conn};
        setup.exec("CREATE TEMP TABLE IF NOT EXISTS accounts (id INT PRIMARY KEY, balance DECIMAL)");
        setup.exec("INSERT INTO accounts VALUES (1, 1000), (2, 500) ON CONFLICT DO NOTHING");
        setup.commit();

        // ---------- Successful transaction ----------
        {
            pqxx::work txn{conn};

            // Deduct from account 1
            txn.exec("UPDATE accounts SET balance = balance - 200 WHERE id = 1");

            // Add to account 2
            txn.exec("UPDATE accounts SET balance = balance + 200 WHERE id = 2");

            txn.commit();  // Explicit commit
            std::cout << "Transfer of 200 completed.\n";
        }

        {
            pqxx::work txn{conn};

            txn.exec("UPDATE accounts SET balance = balance - 300 WHERE id = 1");
            txn.exec("UPDATE accounts SET balance = balance + 300 WHERE id = 3");  // id=3 does not exist!

            // If an exception is thrown, txn's destructor rolls back automatically.
            // But here we catch the error and abort early.
            try {
                // Simulate a condition that forces a rollback
                throw std::runtime_error("Something went wrong, rolling back.");
            } catch (...) {
                std::cerr << "Error occurred. Rolling back transaction.\n";
                // txn destructor will rollback, no commit is called
                return 1;  // exit without commit
            }
            txn.commit();
        }
    } catch (std::exception const& e) {
        std::cerr << "Unhandled exception: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
#include <iostream>
#include <fstream>
#include <pqxx/pqxx>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <conninfo> <csv_file>\n";
        return 1;
    }

    try {
        std::string conn_str = argv[1];
        std::string csv_file  = argv[2];

        pqxx::connection conn{conn_str};

        // Create target table (will be destroyed on disconnect)
        pqxx::work setup{conn};
        setup.exec("CREATE TEMP TABLE IF NOT EXISTS bulk_data (col1 TEXT, col2 INT, col3 DATE)");
        setup.commit();

        // Open CSV file
        std::ifstream in{csv_file};
        if (!in) {
            std::cerr << "Cannot open " << csv_file << "\n";
            return 1;
        }

        // Use stream_to to COPY from file stream
        pqxx::work tx{conn};
        auto stream = pqxx::stream_to::table(tx, {"bulk_data"}, {"col1", "col2", "col3"});

        std::string line;
        while (std::getline(in, line)) {
            // stream_to expects tab-separated fields by default; for CSV, we use the raw stream
            stream.write_raw_line(line);
        }
        stream.complete();  // finish the COPY
        tx.commit();

        std::cout << "Data copied successfully.\n";

    } catch (std::exception const& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
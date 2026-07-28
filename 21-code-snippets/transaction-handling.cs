using System;
using Npgsql;

class Program
{
    static void Main(string[] args)
    {
        string connString = args.Length > 0
            ? args[0]
            : "Host=localhost;Database=postgres;Username=postgres";

        try
        {
            using var conn = new NpgsqlConnection(connString);
            conn.Open();

            // Create temporary table and seed data
            using (var setupCmd = new NpgsqlCommand(
                @"CREATE TEMP TABLE IF NOT EXISTS accounts (
                    id INT PRIMARY KEY,
                    balance DECIMAL
                  );

                  INSERT INTO accounts VALUES (1, 1000), (2, 500)
                  ON CONFLICT (id) DO NOTHING;", conn))
            {
                setupCmd.ExecuteNonQuery();
            }

            // ---------- Successful transaction ----------
            using (var tx = conn.BeginTransaction())
            {
                try
                {
                    using var deductCmd = new NpgsqlCommand(
                        "UPDATE accounts SET balance = balance - 200 WHERE id = 1", conn, tx);
                    deductCmd.ExecuteNonQuery();

                    using var addCmd = new NpgsqlCommand(
                        "UPDATE accounts SET balance = balance + 200 WHERE id = 2", conn, tx);
                    addCmd.ExecuteNonQuery();

                    tx.Commit();
                    Console.WriteLine("Transfer of 200 completed successfully.");
                }
                catch
                {
                    tx.Rollback();
                    Console.Error.WriteLine("Transfer failed. Rolled back.");
                    throw;
                }
            }

            // ---------- Transaction that will be rolled back ----------
            using (var tx = conn.BeginTransaction())
            {
                try
                {
                    using var deductCmd = new NpgsqlCommand(
                        "UPDATE accounts SET balance = balance - 300 WHERE id = 1", conn, tx);
                    deductCmd.ExecuteNonQuery();

                    // This will fail because account with id=3 does not exist
                    using var addCmd = new NpgsqlCommand(
                        "UPDATE accounts SET balance = balance + 300 WHERE id = 3", conn, tx);
                    int rowsAffected = addCmd.ExecuteNonQuery();

                    // If we reach here, commit. Otherwise the catch block rolls back.
                    tx.Commit();
                }
                catch (Exception ex)
                {
                    tx.Rollback();
                    Console.Error.WriteLine($"Transaction rolled back: {ex.Message}");
                }
            }

            // Show final balances
            using var checkCmd = new NpgsqlCommand("SELECT id, balance FROM accounts ORDER BY id", conn);
            using var reader = checkCmd.ExecuteReader();
            Console.WriteLine("\nFinal balances:");
            while (reader.Read())
                Console.WriteLine($"Account {reader.GetInt32(0)}: {reader.GetDecimal(1)}");
        }
        catch (Exception ex)
        {
            Console.Error.WriteLine($"Fatal error: {ex.Message}");
            Environment.Exit(1);
        }
    }
}
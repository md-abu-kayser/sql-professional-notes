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
            // NpgsqlConnection implements IDisposable – using ensures cleanup
            using var conn = new NpgsqlConnection(connString);
            conn.Open();
            Console.WriteLine($"Connected to {conn.Database} on {conn.Host}");

            // Execute a query
            string sql = @"SELECT schemaname, tablename
                           FROM pg_tables
                           WHERE tableowner = current_user
                           LIMIT 10";

            using var cmd = new NpgsqlCommand(sql, conn);
            using var reader = cmd.ExecuteReader();

            // Print column headers
            for (int i = 0; i < reader.FieldCount; i++)
                Console.Write($"{reader.GetName(i),-30}");
            Console.WriteLine();
            Console.WriteLine(new string('-', 60));

            // Iterate rows
            while (reader.Read())
            {
                for (int i = 0; i < reader.FieldCount; i++)
                    Console.Write($"{reader[i],-30}");
                Console.WriteLine();
            }

            Console.WriteLine($"\nRows returned: {reader.RecordsAffected}");
        }
        catch (Exception ex)
        {
            Console.Error.WriteLine($"Error: {ex.Message}");
            Environment.Exit(1);
        }
    }
}
-- Random N rows
SELECT * FROM users ORDER BY RANDOM() LIMIT 10; -- PostgreSQL
SELECT * FROM users ORDER BY RAND() LIMIT 10;   -- MySQL
-- Bernoulli sampling (PostgreSQL)
SELECT * FROM users TABLESAMPLE BERNOULLI(10);
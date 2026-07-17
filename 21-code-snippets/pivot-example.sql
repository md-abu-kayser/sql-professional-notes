-- Pivoting rows into columns

-- Portable approach using CASE + aggregation (works everywhere)
SELECT
    product_id,
    SUM(CASE WHEN quarter = 'Q1' THEN revenue ELSE 0 END) AS q1,
    SUM(CASE WHEN quarter = 'Q2' THEN revenue ELSE 0 END) AS q2,
    SUM(CASE WHEN quarter = 'Q3' THEN revenue ELSE 0 END) AS q3,
    SUM(CASE WHEN quarter = 'Q4' THEN revenue ELSE 0 END) AS q4
FROM quarterly_sales
GROUP BY product_id;

-- PostgreSQL: crosstab() from the tablefunc extension
-- CREATE EXTENSION IF NOT EXISTS tablefunc;
-- SELECT * FROM crosstab(
--   'SELECT product_id, quarter, revenue FROM quarterly_sales ORDER BY 1,2'
-- ) AS ct(product_id int, q1 numeric, q2 numeric, q3 numeric, q4 numeric);

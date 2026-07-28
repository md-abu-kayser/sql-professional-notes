-- PostgreSQL crosstab
SELECT * FROM crosstab(
  'SELECT department, month, sum(sales) FROM sales GROUP BY 1,2 ORDER BY 1,2',
  'SELECT generate_series(1,12)'
) AS (department text, jan numeric, feb numeric, ...);
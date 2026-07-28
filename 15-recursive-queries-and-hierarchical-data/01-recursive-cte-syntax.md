# Recursive CTE Syntax

```sql
WITH RECURSIVE cte AS (
  SELECT ... UNION ALL SELECT ... FROM cte ...
)
SELECT * FROM cte;
```

# Self‑Joins

Join a table to itself. Use aliases.

```sql
SELECT e.name, m.name AS manager
FROM employees e
LEFT JOIN employees m ON e.manager_id = m.id;
```

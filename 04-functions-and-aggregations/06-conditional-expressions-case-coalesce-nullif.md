# Conditional Expressions

```sql
SELECT name,
  CASE WHEN age < 18 THEN 'minor' ELSE 'adult' END AS status,
  COALESCE(phone, 'N/A') AS phone,
  NULLIF(a, b)
FROM users;
```

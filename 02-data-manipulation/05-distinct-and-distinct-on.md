# DISTINCT & DISTINCT ON

```sql
SELECT DISTINCT country FROM users;
-- PostgreSQL specific: DISTINCT ON
SELECT DISTINCT ON (country) country, name FROM users ORDER BY country, created_at DESC;
```

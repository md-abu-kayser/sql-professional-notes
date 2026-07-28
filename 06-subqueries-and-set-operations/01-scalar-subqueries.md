# Scalar Subqueries

A subquery returning single value. Can be used in `SELECT`, `WHERE`.

```sql
SELECT name, (SELECT COUNT(*) FROM orders WHERE user_id = users.id) AS order_count
FROM users;
```

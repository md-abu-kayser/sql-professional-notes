# INSERT Multiple Rows & SELECT INTO

```sql
INSERT INTO users (name, email) VALUES ('A', 'a@b.com'), ('B', 'b@b.com');
INSERT INTO active_users (id, name) SELECT id, name FROM users WHERE active = true;
```

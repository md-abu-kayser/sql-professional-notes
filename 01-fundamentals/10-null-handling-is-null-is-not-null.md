# NULL Handling

`NULL` means unknown. Use `IS NULL` / `IS NOT NULL` for filtering.

```sql
SELECT * FROM users WHERE phone IS NULL;
SELECT COALESCE(phone, 'N/A') AS contact_phone FROM users;
```

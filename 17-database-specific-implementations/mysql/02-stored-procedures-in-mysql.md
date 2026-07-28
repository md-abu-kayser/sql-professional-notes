# Stored Procedures in MySQL

```sql
DELIMITER //
CREATE PROCEDURE myproc()
BEGIN
  SELECT * FROM users;
END //
DELIMITER ;
```

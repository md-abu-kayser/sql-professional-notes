# Creating Databases & Tables

```sql
CREATE DATABASE mydb;
CREATE TABLE users (
  id INTEGER PRIMARY KEY,
  name VARCHAR(100) NOT NULL,
  email VARCHAR(255) UNIQUE
);
```

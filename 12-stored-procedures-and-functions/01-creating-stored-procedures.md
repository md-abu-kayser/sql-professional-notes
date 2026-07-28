# Creating Stored Procedures

```sql
CREATE PROCEDURE update_price(product_id INT, new_price DECIMAL)
LANGUAGE SQL
AS $$
  UPDATE products SET price = new_price WHERE id = product_id;
$$;
```

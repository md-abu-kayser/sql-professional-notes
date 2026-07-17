-- UPSERT patterns across engines

-- PostgreSQL / SQLite: INSERT ... ON CONFLICT
INSERT INTO inventory (sku, quantity)
VALUES ('ABC-123', 10)
ON CONFLICT (sku)
DO UPDATE SET quantity = inventory.quantity + EXCLUDED.quantity;

-- MySQL: INSERT ... ON DUPLICATE KEY UPDATE
INSERT INTO inventory (sku, quantity)
VALUES ('ABC-123', 10)
ON DUPLICATE KEY UPDATE quantity = quantity + VALUES(quantity);

-- SQL Server / Oracle: MERGE
MERGE INTO inventory AS target
USING (SELECT 'ABC-123' AS sku, 10 AS quantity) AS source
ON target.sku = source.sku
WHEN MATCHED THEN
    UPDATE SET target.quantity = target.quantity + source.quantity
WHEN NOT MATCHED THEN
    INSERT (sku, quantity) VALUES (source.sku, source.quantity);

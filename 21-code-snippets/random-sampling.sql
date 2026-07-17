-- Random row sampling patterns

-- PostgreSQL: fast approximate sampling from large tables
SELECT * FROM big_table TABLESAMPLE SYSTEM (1);  -- ~1% of table

-- PostgreSQL: exact random sample, small tables only (ORDER BY random() is slow at scale)
SELECT * FROM small_table ORDER BY random() LIMIT 10;

-- MySQL: random sample
SELECT * FROM small_table ORDER BY RAND() LIMIT 10;

-- Better at scale: sample by random primary key range
SELECT * FROM big_table
WHERE id >= (SELECT floor(random() * (SELECT max(id) FROM big_table)))
ORDER BY id
LIMIT 10;

-- Pagination pattern using LIMIT / OFFSET and keyset (seek) pagination
-- 1) Simple offset pagination (fine for small offsets, slow for deep pages)
SELECT id, title, created_at
FROM articles
ORDER BY created_at DESC, id DESC
LIMIT 20 OFFSET 40;  -- page 3, 20 rows per page

-- 2) Keyset / seek pagination (fast, stable under inserts)
-- Pass the last seen (created_at, id) from the previous page as parameters
SELECT id, title, created_at
FROM articles
WHERE (created_at, id) < (:last_created_at, :last_id)
ORDER BY created_at DESC, id DESC
LIMIT 20;

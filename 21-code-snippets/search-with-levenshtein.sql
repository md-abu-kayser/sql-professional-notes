-- Fuzzy text search using edit distance / trigram similarity

-- PostgreSQL: fuzzystrmatch extension for Levenshtein distance
-- CREATE EXTENSION IF NOT EXISTS fuzzystrmatch;
SELECT name, levenshtein(name, 'jonathon')
FROM customers
WHERE levenshtein(name, 'jonathon') <= 3
ORDER BY levenshtein(name, 'jonathon');

-- PostgreSQL: pg_trgm for similarity-based fuzzy search (better for larger tables)
-- CREATE EXTENSION IF NOT EXISTS pg_trgm;
SELECT name, similarity(name, 'jonathon') AS score
FROM customers
WHERE name % 'jonathon'
ORDER BY score DESC;

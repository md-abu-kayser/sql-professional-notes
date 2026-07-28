-- PostgreSQL with fuzzystrmatch extension
CREATE EXTENSION fuzzystrmatch;
SELECT * FROM users WHERE levenshtein(name, 'Alice') <= 2;
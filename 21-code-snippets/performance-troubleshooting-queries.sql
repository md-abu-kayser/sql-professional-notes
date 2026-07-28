-- PostgreSQL: running queries
SELECT pid, query, now() - query_start AS duration FROM pg_stat_activity WHERE state = 'active';
-- MySQL: show processlist
SHOW FULL PROCESSLIST;
-- Index usage
SELECT relname, indexrelname, idx_scan FROM pg_stat_user_indexes;
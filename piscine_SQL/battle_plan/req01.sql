WITH RECURSIVE fib AS (
    SELECT
        1 AS n,
        1::bigint AS fibn,
        1::bigint AS fibn_1
    UNION ALL
    SELECT
        n + 1 AS n,
        fibn_1 AS fibn,
        fibn + fibn_1 AS fibn_1
    FROM fib
    WHERE n < 80
)

SELECT
    n,
    fibn
FROM fib;

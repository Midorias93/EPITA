SELECT *
FROM (
    VALUES
    ('a', 3),
    ('b', 1),
    ('b', 3),
    ('c', 1)
) AS answers(question, choice)

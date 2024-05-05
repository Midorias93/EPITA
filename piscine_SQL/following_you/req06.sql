(
    select person_id,
        validation,
        created_at
    from transport.metro_usage_logs
    where created_at between '2059-12-03 12:00:00' and '2059-12-03 14:00:00'
)
union
(
    select person_id,
        validation,
        created_at
    from transport.metro_usage_logs
    where created_at between '2059-12-03 20:00:00' and '2059-12-03 22:00:00'
    limit 10
)
order by created_at desc;

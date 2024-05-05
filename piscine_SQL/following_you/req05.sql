(
    select person_id,
        first_name as person_first_name,
        last_name as person_last_name,
        created_at,
        'street' as place,
        street_id as place_id
        from public.street_logs as S
        join public.people as P on S.person_id = P.id
        where created_at between '2059-12-03 17:00:00' and '2059-12-03 22:00:00'
)
union
(
    select person_id,
        first_name as person_first_name,
        last_name as person_last_name,
        created_at,
        'shop' as place,
        shop_id as place_id
        from public.shop_entrance_logs as S
        join public.people as P on S.person_id = P.id
        where created_at between '2059-12-03 17:00:00' and '2059-12-03 22:00:00'
)
union
(
    select person_id,
        first_name as person_first_name,
        last_name as person_last_name,
        created_at,
        'metro' as place,
        station_id as place_id
        from transport.metro_usage_logs as M
        join public.people as P on M.person_id = P.id
        where created_at between '2059-12-03 17:00:00' and '2059-12-03 22:00:00'
)
order by created_at asc, person_id asc;

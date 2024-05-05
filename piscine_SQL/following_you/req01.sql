select id,
    first_name,
    last_name
from public.people as people
where exists
(
    select 1 from transport.metro_usage_logs as M
    where people.id = M.person_id
    and station_id in (
        select id from transport.metro_stations 
        where name = 'Morgane Abeille'
    )
);

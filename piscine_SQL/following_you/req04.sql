(
select 'metro' as place_type,
    count(id) as entries,
    station_id as place_id
from transport.metro_usage_logs
group by station_id
)
union
(
select 'shop' as place_type,
    count(id) as entries,
    shop_id as place_id
from public.shop_entrance_logs
where transit_type = 'ENTER'
group by shop_id
)
order by entries desc, place_id,place_type desc;

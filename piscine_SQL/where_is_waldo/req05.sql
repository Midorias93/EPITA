select distinct employee_id,
    person_id,
    first_name,
    last_name
from nexus_stores.employees as E
join public.people as P on E.person_id = P.id
join nexus_stores.cashier_shifts as C on C.employee_id = E.id
where C.start_timestamp::date = date '2059-12-01'
and E.store_id = 78
and employee_id not in
(
    select employee_id from
    nexus_stores.employees as E
    join public.people as P on E.person_id = P.id
    join nexus_stores.cashier_shifts as C on C.employee_id = E.id
    where E.store_id = 78 and  '2059-12-01 14:47:07' between C.start_timestamp
    and C.end_timestamp
)
order by person_id desc;

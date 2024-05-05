select id,
    street_id,
    created_at,
    person_id
from backup.street_logs
where
    id not in (select id from public.street_logs);

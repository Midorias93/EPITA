select *
from public.traffic_violations
where license_plate like 'AZ__36_'
and violation_date between timestamp '2059-12-3 21:00' - interval '1 hour'and timestamp '2059-12-3 21:00' + '1 hour'
and (description = 'SPEED_AND_TRAFFIC_VIOLATION' or description = 'RECKLESS_AND_DANGEROUS_DRIVING');

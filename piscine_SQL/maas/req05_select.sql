select geo.name as zone_name,
count(distinct data_center_id) as data_center_count,
count(*) as total_servers,
sum(core_count) as total_cores,
sum(ram) as total_ram,
sum(storage) as total_storage
from memorin.server_hierarchy as server
join memorin.geographic_zones as geo on server.zone_id = geo.id
group by name
order by data_center_count desc, total_servers desc, name;

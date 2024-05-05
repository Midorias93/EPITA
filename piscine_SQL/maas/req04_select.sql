refresh materialized view memorin.outdated_devices;
select * from memorin.outdated_devices
order by versions_behind desc, serial_number;

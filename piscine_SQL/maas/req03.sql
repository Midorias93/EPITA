create view memorin.zoned_devices_logs as
(
    select device_serial,
        version_id,
        zone_id,
        latitude as lat,
        longitude as long,
        temperature as temp,
        battery_percentage as battery,
        signal_strength
    from memorin.device_logs as device
    where temperature  between 34 and 45
    and signal_strength between 0 and 5
    and battery_percentage between 0 and 100
    and longitude between (
        select min_longitude 
        from memorin.geographic_zones as longa
        where longa.id = device.zone_id
    )
    and (
        select max_longitude 
        from memorin.geographic_zones as longb
        where longb.id = device.zone_id
    )
    and latitude between(
        select min_latitude
        from memorin.geographic_zones as lata
        where lata.id = device.zone_id
    )
    and (
        select max_latitude
        from memorin.geographic_zones as latb
        where latb.id = device.zone_id
    )
    and device_serial in (
        select serial_number
        from  memorin.devices as serial
        where device.device_serial = serial.serial_number
        and deactivated_at is null
    )
    and version_id in (
        select id
        from  memorin.device_versions as version
        where version.id = device.version_id
    )
)
with check option;

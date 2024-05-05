create temporary view devices_metrics as
(
    select device_serial,
        L.version_id,
        id as log_id,
        latitude as lat,
        longitude as long,
        temperature as temp,
        battery_percentage as battery,
        signal_strength
    from memorin.device_logs as L join memorin.devices as D on L.device_serial = D.serial_number
    where deactivated_at is null
    order by device_serial, string_to_array(L.version_id,'.')::int[] desc, id
);

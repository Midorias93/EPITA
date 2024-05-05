create materialized view memorin.outdated_devices as
(
    select device.serial_number,
        device.version_id,
        version.released_at,
        version.eol_timestamp,
        (
            select count(*)
            from memorin.device_versions as v
            where version.released_at < v.released_at
        ) as versions_behind
    from memorin.devices device
    join memorin.device_versions as version on version.id = device.version_id
    where version.released_at < (
        select max(released_at)
            from memorin.device_versions as v
            where version.released_at < v.released_at
        )
        and device.deactivated_at is null
);

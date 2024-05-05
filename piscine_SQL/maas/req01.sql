create view memorin.devices_summary as
(
    select count(*) as total_devices,
        count(*) FILTER ( where deactivated_at is null ) as active_devices,
        count(*) FILTER ( where deactivated_at is not null ) as inactive_devices
        from memorin.devices
);

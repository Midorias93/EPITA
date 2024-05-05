create recursive view memorin.server_hierarchy
(
    id,
    zone_id,
    core_count,
    ram,
    storage,
    data_center_id
)
as
(
    (
    select
        id,
        zone_id,
        core_count,
        ram,
        storage,
        id as master_id
    from memorin.servers as server
    where master_id is null
    )
    union all
    (
        select
        server.id,
        server.zone_id,
        server.core_count,
        server.ram,
        server.storage,
        server_hierarchy.data_center_id
    from memorin.servers as server
    join server_hierarchy
    on server.master_id = server_hierarchy.id
    )
);

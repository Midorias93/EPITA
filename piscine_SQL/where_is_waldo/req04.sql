insert into nexus_stores.sales (
    id,
    product_id,
    checkout_id,
    store_id,
    sale_timestamp
)

select
    '0000000a',
    3,
    '68cdd3ec',
    78,
    '2059-12-01 14:47:07';

insert into nexus_stores.cashier_shifts (
    id,
    checkout_id,
    employee_id,
    store_id,
    start_timestamp,
    end_timestamp
)
select
    '0000000a',
    '68cdd3ec',
    null,
    78,
    '2059-12-01 13:00',
    '2059-12-01 15:00';

create table dtf.shifts_and_sales_78
(
    sales_id text,
    product_id integer,
    checkout_id text,
    sale_timestamp timestamp,
    shift_id text,
    employee_id text,
    shift_start_timestamp timestamp,
    shift_end_timestamp timestamp
);

insert into dtf.shifts_and_sales_78
(
    sales_id,
    product_id,
    checkout_id,
    sale_timestamp,
    shift_id,
    employee_id,
    shift_start_timestamp,
    shift_end_timestamp
)
select
    S.id,
    S.product_id,
    S.checkout_id,
    S.sale_timestamp,
    C.id,
    C.employee_id,
    C.start_timestamp,
    C.end_timestamp
from nexus_stores.sales as S
join nexus_stores.cashier_shifts as C on S.checkout_id = C.checkout_id
where S.store_id = 78
and "start_timestamp" <= timestamp '2059-12-01 14:47:07'
and "end_timestamp" >= timestamp '2059-12-01 14:47:07';

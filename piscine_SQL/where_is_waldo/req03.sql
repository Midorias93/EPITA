select Ca.id,
    Ca.checkout_id,
    Ca.employee_id,
    Ch.store_id as checkout_store_id,
    Ca.store_id as shift_store_id,
    Ca.start_timestamp,
    Ca.end_timestamp
from nexus_stores.checkouts as Ch
join nexus_stores.cashier_shifts Ca on Ch.id = Ca.checkout_id;

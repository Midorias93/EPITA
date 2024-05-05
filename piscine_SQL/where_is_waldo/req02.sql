select count (C.id) filter (where employee_id is null) as null_employee_id_rows_count,
    count(C.id) filter(where C.store_id is null) as null_store_id_rows_count
from nexus_stores.cashier_shifts C join nexus_stores.checkouts as Ch on C.checkout_id = Ch.id;

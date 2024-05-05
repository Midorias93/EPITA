select nexus_stores.receipts.purchase_date, nexus_stores.receipts.first_name, nexus_stores.receipts.last_name, nexus_stores.receipts.email, nexus_stores.products.name, nexus_stores.products.price, nexus_stores.products.category
from nexus_stores.products join nexus_stores.receipt_items
on nexus_stores.receipt_items.product_id = nexus_stores.products.id
join nexus_stores.receipts
on nexus_stores.receipts.id = nexus_stores.receipt_items.receipt_id
where nexus_stores.products.name ilike '%apple%'
and nexus_stores.receipts.email similar to 's(e|a)m[a-z]{3,6}(_)w[a-z]{6}[0-9]{0,}@(roger_)[a-z]{1,}.[a-z]{3}';


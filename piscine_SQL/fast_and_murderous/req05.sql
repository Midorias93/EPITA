select nexus_stores.receipt_items.receipt_id, nexus_stores.products.name,
nexus_stores.receipt_items.quantity, nexus_stores.products.price
from nexus_stores.receipt_items join nexus_stores.products
on nexus_stores.receipt_items.product_id = nexus_stores.products.id
where nexus_stores.products.name ilike '%apple%'
and nexus_stores.receipt_items.quantity > 10;

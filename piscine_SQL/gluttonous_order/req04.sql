insert into public.scrooge_eats_basket_items (order_id, item_id, quantity)
values
    (10000, (select id from public.scrooge_eats_items where name = 'Tacos'), 1),
    (10000, (select id from public.scrooge_eats_items where name = 'Coca-Cola'), 1),
    (10000, (select id from public.scrooge_eats_items where name = 'Kinder Bueno White'), 1);

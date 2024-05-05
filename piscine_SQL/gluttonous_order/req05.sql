insert into public.scrooge_eats_orders(id, account_id,ordered_at, total_price)
values
    (10001, (select id
from public.scrooge_eats_accounts
where company_id = (
        select id
        from public.companies
        where name = 'DTF'
    )), now(), 0);
insert into public.scrooge_eats_basket_items (order_id, item_id, quantity)
values
    (10001, (select id from public.scrooge_eats_items where name = 'Tomato soup'), 1),
    (10001, (select id from public.scrooge_eats_items where name = 'Mojito'), 1);

insert into public.scrooge_eats_orders(id, account_id,ordered_at, total_price)
values
    (10000, (select id
from public.scrooge_eats_accounts
where company_id = (
        select id
        from public.companies
        where name = 'DTF'
    )), now(), 0);

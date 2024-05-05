select id
from public.scrooge_eats_accounts
where company_id = (
        select id
        from public.companies
        where name = 'DTF'
    );

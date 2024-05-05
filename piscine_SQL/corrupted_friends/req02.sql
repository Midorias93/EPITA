insert into dtf.madelines_contacts (
    id,
    title,
    first_name,
    last_name,
    phone,
    email,
    favorite,
    created_at
)
select
    id,
    cast(upper(substring(regexp_replace(full_name, '[^[:ascii:]]|[0-9]', '','g') from '^[a-zA-Z]{2,3}')) as public.prefix),
    initcap(trim (both from substring(regexp_replace(full_name, '[^[:ascii:]]|[0-9]', '','g') from ' [^ ]* '), ' ')),
    initcap(trim (both from substring(regexp_replace(full_name, '[^[:ascii:]]|[0-9]', '','g') from ' [^ ]*$'), ' ')),
    concat(
        lpad(trim(both from substring(regexp_replace(phone,'[^0-9\-\.]','','g') from '^[^.-]*[.-]'), '-.'),3, '0'), '.',
        lpad(trim(both from substring(regexp_replace(phone,'[^0-9\-\.]','','g') from '[.-].*[.-]'), '-.'),3, '0'), '.',
        lpad(trim(both from substring(regexp_replace(phone,'[^0-9\-\.]','','g') from '[.-][^-.]*$'),'-.'),3, '0')
    ),
    trim (from regexp_replace(email, '[^[:ascii:]]','','g'), ''),
    cast(favorite as boolean),
    cast(created_at as timestamp)
from dtf.madelines_contacts_corrupted;

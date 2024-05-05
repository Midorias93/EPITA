create type public.prefix as enum
(
    'MRS',
    'MS',
    'MR',
    'DR'
);

create table dtf.madelines_contacts
(
    id serial PRIMARY KEY,
    title public.prefix,
    first_name text,
    last_name text,
    phone text,
    email text,
    favorite boolean,
    created_at timestamp
);

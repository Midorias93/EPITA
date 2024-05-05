create table nexus_intranet.onboarding_info
(
    manager_id serial primary key references nexus_intranet.nexus_employees (id),
    division nexus_intranet.division_type,
    ssh_key_name varchar(255),
    ssh_key_value varchar(4096),
    tag varchar(54)
);

with recursive "get_h" as (
    (
        select id,
            manager_id
        from nexus_intranet.nexus_employees
        where first_name = 'Arthur'
        and last_name = 'Polard'
    )
    union all
    (
        select
            nexus_intranet.nexus_employees.id,
            nexus_intranet.nexus_employees.manager_id
        from nexus_intranet.nexus_employees
        inner join "get_h" on nexus_intranet.nexus_employees.id = "get_h".manager_id
    )
),

"division_ma" as (
    select division
    from nexus_intranet.nexus_employees
    where 
        first_name = 'Arthur'
        and last_name = 'Polard'
),

"number_colleagues" as (
    select id
    from nexus_intranet.nexus_employees
    where manager_id in (select id
        from nexus_intranet.nexus_employees
        where first_name = 'Arthur'
        and last_name = 'Polard')
),

"tag_manager" as (
    select right(left(tag, 8), 5)
    from nexus_intranet.nexus_employees
        where first_name = 'Arthur'
        and last_name = 'Polard'
),

"tag" as (select concat
    (
        'N',
        (select * from "division_ma"),
        lpad(cast((select count(*) + 1 from "get_h") as text), 2, '0'),
        lpad(cast((select count(id) from "number_colleagues") as text),3,'0'),
        '-',
        (select * from "tag_manager")
    )
)

insert into nexus_intranet.onboarding_info (manager_id, division, ssh_key_name, ssh_key_value, tag)
select
    (select id from nexus_intranet.nexus_employees 
        where first_name = 'Arthur'
        and last_name = 'Polard'),
    'RD',
    'arch_home',
    'ssh-rsa SWV0OUUzcXBSSm4yRUo2cURQSVhEekx3S04ybElKOGQ4ck1zdHZpMndqRlROTHZHVjhHMVg2ZG92aVdFVnB3VkhVTz00a0RFM1NwTHhxZjZzclprY1VsQ2NYbDloPXRlZkFYQXlYQWVmZk1HR0ZNdzhkSDdmNngxUXBlTWhjK3JuWjFNUXJnbEdpRWwrSXBFQnZqU3U9a3lIelFsaD1pV1E2amU5VElacGdBVy92TjRXL0F5cFNLdGcwS216U2MvSXB5QWV5VmY1Z3cyUGE3YnhoRU80Zy85Sz1GPUpVUURGeGRwMy9qR2NqRWF3WGZBbUdXS0NzPTl4VzI1UjhBNVREQUhjZXRhaTdUaG1VYTBIZVlqZnVSTUx3TEtZR0NKcDZ5VjRVUzdVMVBQSFdFeG5zVzBweVRNcGQ9Z3lOQUx4N01acXNxUHVYeUtna0JHbmorV1VIZmVBbDBFdXA9dDBFV3BtQysxZVd5KzlKRzkxbHpr',
    (select * from "tag");

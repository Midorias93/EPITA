create schema if not exists migration;

drop table if exists migration.companies;
create table if not exists migration.companies
(
    like public.companies including all
);
insert into migration.companies
select *
from public.companies;

drop table if exists migration.jobs;
create table if not exists migration.jobs
(
    like public.jobs including all
);
insert into migration.jobs
select *
from public.jobs;

drop table if exists migration.patients_records;
create table if not exists migration.patients_records
(
    like public.patients_records including all
);
insert into migration.patients_records
select *
from public.patients_records;

drop table if exists migration.medical_record_entries;
create table if not exists migration.medical_record_entries
(
    like public.medical_record_entries including all 
);
insert into migration.medical_record_entries
select *
from public.medical_record_entries;

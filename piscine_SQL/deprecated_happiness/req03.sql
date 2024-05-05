alter table migration.companies
add growth numeric(6, 2) not null check(abs(growth) <= 1000 and growth >= 0) default 0;

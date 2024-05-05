create schema nexus;
create schema nexus_it;
create schema techwave;
create schema finstar;
create schema nexus_food;
create schema guardforce;

create type nexus.position as ENUM
(
    'JUNIOR',
    'SENIOR',
    'MANAGER',
    'DIRECTOR'
);

create type nexus.relationship_type as ENUM
(
    'PARENT',
    'SUBSIDIARY',
    'AFFILIATE'
);

create type nexus_food.nutriscore as ENUM
(
    'A',
    'B',
    'C',
    'D',
    'E'
);

create table nexus.employees
(
    id serial PRIMARY KEY,
    first_name varchar(25),
    last_name varchar(25),
    employee_position nexus.position,
    salary numeric(10, 2)
);
create table nexus_it.employees
(
    id serial PRIMARY KEY,
    first_name varchar(25),
    last_name varchar(25),
    employee_position nexus.position,
    salary numeric(10, 2)
);
create table techwave.employees
(
    id serial PRIMARY KEY,
    first_name varchar(25),
    last_name varchar(25),
    employee_position nexus.position,
    salary numeric(10, 2)
);
create table finstar.employees
(
    id serial PRIMARY KEY,
    first_name varchar(25),
    last_name varchar(25),
    employee_position nexus.position,
    salary numeric(10, 2)
);
create table nexus_food.employees
(
    id serial PRIMARY KEY,
    first_name varchar(25),
    last_name varchar(25),
    employee_position nexus.position,
    salary numeric(10, 2)
);
create table guardforce.employees
(
    id serial PRIMARY KEY,
    first_name varchar(25),
    last_name varchar(25),
    employee_position nexus.position,
    salary numeric(10, 2)
);

create table nexus.nexus_relations
(
    id serial PRIMARY KEY,
    parent_company varchar(25),
    child_company varchar(25),
    relationship_type nexus.relationship_type
);

create table nexus_it.software_assets
(
    id serial PRIMARY KEY,
    software_name varchar(50),
    license_key uuid,
    expiration_date date
);

create table techwave.project_milestones
(
    id serial PRIMARY KEY,
    milestone_name varchar(50),
    due_date date,
    completion_status boolean
);

create table finstar.investments
(
    id serial PRIMARY KEY,
    investment_name varchar(50),
    investment_type varchar(25),
    amount_invested numeric(15, 5),
    date_invested date
);

create table nexus_food.products
(
    id serial PRIMARY KEY,
    product_name varchar(25),
    product_nutriscore nexus_food.nutriscore
);

create table guardforce.incident_reports
(
    id serial PRIMARY KEY,
    incident_description text,
    incident_date timestamp,
    incident_location varchar(50),
    reported_by varchar(50)
);

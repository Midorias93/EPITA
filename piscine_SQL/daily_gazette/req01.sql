create schema rr_times;
create table rr_times.locales
(
    language_code varchar(2) not null check (language_code similar to '[a-z]{2}'),
    country_code varchar(2) not null check (country_code similar to '[A-Z]{2}'),
    name varchar(50) unique not null,
    PRIMARY KEY(language_code, country_code)
);

create table rr_times.translated_articles
(
    id serial PRIMARY KEY,
    title text not null,
    body text not null
);

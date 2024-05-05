create schema if not exists rr_times;

create table rr_times.translated_headlines
(
    id serial PRIMARY KEY,
    title text not null,
    subtitle text
);

create table rr_times.issues
(
    id serial PRIMARY KEY,
    issued_at timestamp not null,
    language varchar(2),
    country varchar(2),
    translated_headline_id integer references rr_times.translated_headlines (id) on delete restrict not null,
    foreign key
    (
        language,
        country
    )references rr_times.locales (language_code, country_code) on delete set null,
    unique(issued_at, language, country)

);

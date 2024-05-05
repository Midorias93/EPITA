create schema if not exists rr_times;

create table rr_times.articles
(
    id serial PRIMARY KEY,
    translated_article_id integer references rr_times.translated_articles (id) on delete cascade,
    rubric_id integer references rr_times.rubrics (id) on delete cascade,
    language varchar(2) not NULL,
    country varchar(2) not NULL,
    foreign key
    (
        language,
        country
    )references rr_times.locales (language_code, country_code) on delete cascade
);

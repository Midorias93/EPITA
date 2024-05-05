create schema if not exists rr_times;

create type rr_times.rubric_theme as enum
(
    'TECHNOLOGY',
    'ECONOMY',
    'HEALTH',
    'SPORT',
    'CULTURE',
    'POLITICS',
    'SCIENCE',
    'TRAVEL',
    'SOCIETY',
    'ENVIRONMENT',
    'EDUCATION',
    'MEDIA',
    'FASHION',
    'ARCHITECTURE',
    'BUSINESS',
    'SPACE'
);

create table rr_times.rubrics
(
    id serial PRIMARY KEY,
    theme rr_times.rubric_theme not null,
    nb_columns integer not null,
    issue_id integer references rr_times.issues (id) on delete cascade,
    unique(theme, issue_id)
);

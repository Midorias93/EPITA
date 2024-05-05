select P.id as person_id,
        P.first_name,
        P.last_name,
        P.birth_date,
        O.created_at as conviction_date,
        O.serving_time,
        O.created_at < timestamp '2059-12-03' - (interval '1 month' * O.serving_time) as could_be_released
into public.outcome_status
from justice.records as R
join justice.outcomes as O on R.outcome_id = O.id
join justice.defendants as D on R.defendants_id = D.id
join public.people as P on P.id = D.person_id
join justice.trials as T on T.id = D.trial_id
join justice.cases as C on T.case_id = C.id
where
    O.outcome = 'GUILTY'
    and C.classification = 'CRIME';

select P.id as person_id,
        P.first_name,
        P.last_name,
        P.birth_date,
        C.classification,
        C.description
into temporary not_guilty
from justice.records as R
join justice.outcomes as O on R.outcome_id = O.id
join justice.defendants as D on R.defendants_id = D.id
join public.people as P on P.id = D.person_id
join justice.trials as T on T.id = D.trial_id
join justice.cases as C on T.case_id = C.id
where
    O.outcome = 'NOT_GUILTY';

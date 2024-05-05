select P.id as person_id,
        P.first_name,
        P.last_name,
        O.created_at,
        O.serving_time,
        case
            when amount is not null then
                O.created_at + (interval '1 month' * (O.serving_time - amount))
            else
                O.created_at + (interval '1 month' * O.serving_time)
        end as release_date
into public.release_dates
from justice.records as R
join justice.outcomes as O on R.outcome_id = O.id
join justice.defendants as D on R.defendants_id = D.id
join public.people as P on P.id = D.person_id
join justice.trials as T on T.id = D.trial_id
join justice.cases as C on T.case_id = C.id
left join justice.sentence_reductions as S on S.outcome_id = R.outcome_id
where
    O.outcome = 'GUILTY'
order by
    release_date desc;

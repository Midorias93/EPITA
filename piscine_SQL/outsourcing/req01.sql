select justice.trials.id as trial_id, case_id, classification, description
into public.definitive_trials
from justice.trials join justice.cases on justice.trials.case_id = justice.cases.id
where justice.trials.status = 'FINISHED'
order by classification, case_id;

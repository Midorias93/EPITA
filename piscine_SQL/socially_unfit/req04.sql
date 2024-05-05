select distinct first_name, last_name, birth_date, job_id, social_credit_balance from people
where job_id is not null
and social_credit_balance > 0 and death_date is null order by social_credit_balance desc
,birth_date asc ,job_id asc limit 100 offset 200;

select id, person_id, credits_change, action_description
from social_credit_history
where date between '2059-12-03 17:00' and '2059-12-03 22:00'
order by credits_change asc , id asc limit 10;


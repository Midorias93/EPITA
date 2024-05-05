select first_name, last_name, death_date, social_credit_balance from people
order by death_date desc NULLS last, social_credit_balance desc limit 100;

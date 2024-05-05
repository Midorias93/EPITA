CREATE TABLE banking_transactions_poc
(
    id serial PRIMARY KEY,
    sender varchar(22) NOT NULL check (sender similar to '(RR)[0-9]{2}[A-Z]{4}[0-9]{14}'),
    receiver varchar(22) NOT NULL check (receiver similar to '(RR)[0-9]{2}[A-Z]{4}[0-9]{14}'),
    amount numeric(16, 2) NOT NULL check (amount > 0),
    check(sender <> receiver)
);

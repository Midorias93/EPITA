SELECT
    people.first_name,
    people.last_name,
    gusto_tables.number_of_seats AS guest_number,
    round(reservations.bill_total::numeric, 2) AS bill_total
FROM gusto_reservations AS reservations,
    gusto_tables,
    gusto_guests AS guests,
    people
WHERE reservations.table_id = gusto_tables.id
    AND reservations.id = guests.reservation_id
    AND reservations.cancelled = FALSE
    AND guests.guest_id = people.id
    AND people.last_name LIKE concat(reservations.reservation_name, '%')
ORDER BY
    gusto_tables.number_of_seats ASC, reservations.bill_total DESC NULLS LAST
LIMIT 10;

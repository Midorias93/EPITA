select id, reservation_name, reservation_date from gusto_reservations 
where reservation_date between '2059-12-03 18:00' and '2059-12-03 21:00'
and cancelled = false;

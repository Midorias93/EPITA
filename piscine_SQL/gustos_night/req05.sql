select gusto_guests.id, gusto_guests.reservation_id 
from gusto_reservations join gusto_guests on gusto_guests.reservation_id = gusto_reservations.id
where gusto_reservations.reservation_date between '2059-12-03 18:00' and '2059-12-03 21:00'
and gusto_reservations.cancelled = false;

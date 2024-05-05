select concat(employee.first_name,' ', employee.last_name) as employee_name,
    concat(manager.first_name,' ', manager.last_name) as manager_name
from nexus_intranet.nexus_employees as employee
join nexus_intranet.nexus_employees as manager on employee.manager_id = manager.id;

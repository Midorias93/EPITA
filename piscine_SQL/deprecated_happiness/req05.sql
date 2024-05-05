update migration.medical_record_entries
set description = 
    case
    when length(description) > 100 then concat(left(description, 97), '...')
    else description
    end;
alter table migration.medical_record_entries 
alter column description
type varchar(100);

select id,
    filename,
    case
    when decrypted then 'File was successfully decrypted.'
    when
    (select decrypted
        from dtf.madelines_files_results as table_parent
        where table_parent.id = children_table.parent_id
    ) then 'File was successfully decrypted because its containing folder was successfully decrypted.'
    else 'File remains encrypted.'
    end as decryption_status
from dtf.madelines_files_results as children_table
order by id;


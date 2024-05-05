select id,
    size as stored_size,
    decrypted,
    case
        when size is null then taille
        else size
    end as calculated_size
from dtf.madelines_files_results as children_table,
        cast((select avg(size) from dtf.madelines_files_results as parent_table
            where children_table.decrypted = parent_table.decrypted
            and parent_table.parent_id is not null
        ) as bigint) as taille
where parent_id is not null
order by id asc;

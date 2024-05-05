select parent_id as folder_id,
    count(filename) filter (where permissions like '%__x%') as nb_executables
from dtf.madelines_files
group by parent_id
having count(filename) filter (where permissions like '%__x%') >= 3
order by parent_id asc nulls first;

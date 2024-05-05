select owner,
    count(filename) as num_files
from dtf.madelines_files
group by
    owner
having count(filename) = (select min(num_files)
from (select count(filename) as num_files from dtf.madelines_files group by owner) as test)
order by owner asc;

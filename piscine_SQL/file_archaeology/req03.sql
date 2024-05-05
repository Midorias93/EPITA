select filename,
    size
from dtf.madelines_files
where size > ((select avg(size) from dtf.madelines_files) * 75) /100
order by size desc;

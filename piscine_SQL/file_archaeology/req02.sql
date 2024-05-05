select filename,
    size
from dtf.madelines_files
where size = (select max(size) from dtf.madelines_files where created_at between timestamp '2059-12-03 23:59:59' - interval '1 week' and timestamp '2059-12-03')
and created_at between timestamp '2059-12-03 23:59:59' - interval '1 week' and timestamp '2059-12-03'
order by filename;

select min(size) filter (where filename ilike '%secret%') as smallest_secret_file_size,
    min(size) as smallest_file_size
from dtf.madelines_files

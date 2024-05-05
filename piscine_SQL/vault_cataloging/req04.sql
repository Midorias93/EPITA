select cast(avg(rsa_time) as numeric(10,2)) as avg_rsa_time,
    cast(avg(hyper_pulse_time) as numeric(10,2)) as avg_hyper_pulse_time,
    cast(avg(quantum_x_time) as numeric(10,2)) as avg_quantum_x_time,
    cast(avg(aes_time) as numeric(10,2)) as avg_aes_time,
    cast(avg(d_crypt_time) as numeric(10,2)) as avg_d_crypt_time
from
    (select
        coalesce(nullif(rsa_time, 0),
            (select max(rsa_time)
                from dtf.madelines_files_results)) as rsa_time,
        coalesce(nullif(hyper_pulse_time, 0),
            (select max(hyper_pulse_time)
                from dtf.madelines_files_results)) as hyper_pulse_time,
        coalesce(nullif(quantum_x_time, 0),
            (select max(quantum_x_time)
                from dtf.madelines_files_results)) as quantum_x_time,
        coalesce(nullif(aes_time, 0),
            (select max(aes_time)
                from dtf.madelines_files_results)) as aes_time,
        coalesce(nullif(d_crypt_time, 0),
            (select max(d_crypt_time)
                from dtf.madelines_files_results)) as d_crypt_time
        from dtf.madelines_files_results
    ) as ff;

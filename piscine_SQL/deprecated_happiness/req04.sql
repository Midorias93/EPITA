alter table migration.patients_records
add person_id integer references public.people(id);

update migration.patients_records
set person_id = (select person_id
        from medical_confidential.patients_ids
        where medical_confidential.patients_ids.patient_id = migration.patients_records.id
    );

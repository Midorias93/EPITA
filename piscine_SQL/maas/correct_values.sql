INSERT INTO "memorin"."zoned_devices_logs" (
    "device_serial",
    "version_id",
    "zone_id",
    "lat",
    "long",
    "temp",
    "battery",
    "signal_strength"
)
SELECT
    -- The device should not be deactivated
    (
        SELECT "serial_number"
        FROM "memorin"."devices"
        WHERE "deactivated_at" IS NULL
        ORDER BY random()
        LIMIT 1
    ),
    -- The version should only exist
    (
        SELECT "id"
        FROM "memorin"."device_versions"
        ORDER BY random()
        LIMIT 1
    ),
    "zone"."id" AS "zone_id",
    -- Latitude and Longitude should be in the boundary box of the zone
    random() * ("zone"."max_latitude" - "zone"."min_latitude")
    + "zone"."min_latitude" AS "lat",
    random() * ("zone"."max_longitude" - "zone"."min_longitude")
    + "zone"."min_longitude" AS "long",
    -- Temperature should be between 34 and 45
    floor(random() * (45 - 34 + 1) + 34) AS "temp",
    -- Battery percentage should be between 0 and 100
    floor(random() * (100 + 1)) AS "battery",
    -- Signal strength should be between 0 and 5
    floor(random() * (5 + 1)) AS "signal_strength"
FROM
    "memorin"."geographic_zones" AS "zone"
ORDER BY random() LIMIT 1;

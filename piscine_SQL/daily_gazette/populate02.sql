INSERT INTO rr_times.translated_headlines ("title", "subtitle")
VALUES
('Ängste vor dem Bug des Jahres 2038.', 'Der schlimmste Bug seit Jahrzehnten?'),
('Worries about the year 2038 bug.', 'The worst bug in decades?'),
('Craintes autour du bug de l''an 2038.', 'Le pire bug depuis des décennies ?'),
('Die KI-Revolution im Sport', NULL),
('The AI revolution in sport.', NULL),
('La révolution de l''IA dans le sport.', NULL);

INSERT INTO rr_times.issues (
    "issued_at", "language", "country", "translated_headline_id"
) VALUES
('2037-01-01', 'de', 'AT', 1),
('2037-01-01', 'de', 'DE', 1),
('2037-01-01', 'de', 'LU', 1),
('2037-01-01', 'en', 'GB', 2),
('2037-01-01', 'en', 'US', 2),
('2037-01-01', 'fr', 'CA', 3),
('2037-01-01', 'fr', 'FR', 3),
('2037-01-01', 'fr', 'LU', 3),
('2037-01-02', 'de', 'AT', 4),
('2037-01-02', 'de', 'DE', 4),
('2037-01-02', 'de', 'LU', 4),
('2037-01-02', 'en', 'GB', 5),
('2037-01-02', 'en', 'US', 5),
('2037-01-02', 'fr', 'CA', 6),
('2037-01-02', 'fr', 'FR', 6),
('2037-01-02', 'fr', 'LU', 6);

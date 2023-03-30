SELECT AVG(energy) AS ave_energy FROM songs WHERE artist_id IN (SELECT id FROM artists WHERE name IN ("Drake"));

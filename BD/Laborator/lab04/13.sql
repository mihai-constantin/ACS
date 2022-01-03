-- Persoanele care s-au angajat in anul 1980

SELECT
	id_ang AS ecuson,
	nume,
	functie,
	data_ang AS "Data Angajarii"
FROM angajati
WHERE data_ang LIKE '%80';
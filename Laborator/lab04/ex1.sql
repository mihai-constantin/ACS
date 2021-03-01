SELECT
	id_ang AS ecuson,
	nume,
	functie,
	salariu,
	data_ang,
	comision
FROM angajati
WHERE
	data_ang < '1-JAN-1982' AND
	(comision = 0 OR comision IS NULL)
ORDER BY nume;
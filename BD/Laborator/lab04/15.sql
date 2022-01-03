SELECT
	id_ang AS ecuson,
	nume,
	functie,
	salariu,
	comision
FROM angajati
WHERE
	id_dep = 20 AND
	(comision = 0 OR comision IS NULL)
ORDER BY nume;
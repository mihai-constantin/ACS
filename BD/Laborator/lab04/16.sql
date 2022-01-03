SELECT
	id_ang AS ecuson,
	nume,
	functie,
	salariu,
	comision
FROM angajati
WHERE
	lower(functie) = 'salesman' AND
	(comision != 0 AND comision IS NOT NULL)
ORDER BY nume;
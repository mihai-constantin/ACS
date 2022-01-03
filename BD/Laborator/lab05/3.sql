SELECT
	id_dep,
	den_dep,
	nume,
	functie
FROM
	angajati
	NATURAL JOIN departamente
WHERE
	id_dep = 10
ORDER BY 3;
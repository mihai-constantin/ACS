SELECT
	id_dep "Nr. departament",
	nume,
	functie,
	salariu,
	data_ang AS "Data Angajarii"
FROM angajati
WHERE LOWER(functie) = 'manager'
ORDER BY id_dep;
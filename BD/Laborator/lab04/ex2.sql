SELECT
	id_ang AS ecuson,
	nume,
	functie,
	salariu,
	comision
FROM angajati
WHERE
	salariu > 3000 AND
	id_sef IS NULL
ORDER BY id_dep;
SELECT
	id_ang AS ecuson,
	nume,
	functie,
	salariu,
	comision
FROM angajati
WHERE
	lower(functie) = 'analyst' OR
	(lower(functie) = 'manager' AND salariu > 1500)
ORDER BY nume;
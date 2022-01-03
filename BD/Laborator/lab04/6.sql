SELECT 
	id_ang ||'-'|| nume angajat,
	functie,
	id_dep,
	salariu + nvl(comision, 0) AS "venit lunar",
	'			' AS semnatura
FROM angajati
ORDER BY id_dep;
SELECT
	a.nume,
	a.functie,
	2 * a.salariu,
	g.grad
FROM
	grila_salariu g
	FULL OUTER JOIN angajati a
		ON a.salariu * 2 BETWEEN g.nivel_inferior AND g.nivel_superior
ORDER BY 
	a.nume;


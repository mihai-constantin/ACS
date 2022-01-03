-- metoda 1
-- folosind alias
-- SELECT
-- 	d.id_dep,
-- 	d.den_dep,
-- 	a.nume,
-- 	a.functie
-- FROM
-- 	departamente d,
-- 	angajati a
-- WHERE
-- 	d.id_dep = a.id_dep AND
-- 	a.id_dep = 10;

-- metoda 1
-- folosind numele tabelului
-- SELECT
-- 	angajati.id_dep,
-- 	departamente.den_dep,
-- 	angajati.nume,
-- 	angajati.functie
-- FROM
-- 	angajati,
-- 	departamente
-- WHERE
-- 	angajati.id_dep = departamente.id_dep AND
-- 	angajati.id_dep = 10
-- ORDER BY 3;


-- metoda 2 varianta 1
-- SELECT
-- 	a.id_dep,
-- 	d.den_dep,
-- 	a.nume,
-- 	a.functie
-- FROM
-- 	angajati a
-- 	JOIN departamente d
-- 		ON a.id_dep = d.id_dep
-- WHERE
-- 	a.id_dep = 10
-- ORDER BY 3;

-- metoda 2 varianta 2
-- SELECT
-- 	a.id_dep,
-- 	d.den_dep,
-- 	a.nume,
-- 	a.functie
-- FROM
-- 	angajati a
-- 	INNER JOIN departamente d
-- 		ON a.id_dep = d.id_dep
-- WHERE
-- 	a.id_dep = 10
-- ORDER BY 3;


-- metoda 3 varianta 1
-- folosind using
-- SELECT
-- 	id_dep,
-- 	d.den_dep,
-- 	a.nume,
-- 	a.functie
-- FROM
-- 	angajati a
-- 	INNER JOIN departamente d
-- 		USING (id_dep)
-- WHERE
-- 	id_dep = 10
-- ORDER BY 3;

-- metoda 3 varianta 2
-- folosind using
SELECT
	id_dep,
	d.den_dep,
	a.nume,
	a.functie
FROM
	angajati a
	JOIN departamente d
		USING (id_dep)
WHERE
	id_dep = 10
ORDER BY 3;



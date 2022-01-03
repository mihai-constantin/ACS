-- SELECT
-- 	a.nume,
-- 	d1.den_dep,
-- 	a.data_ang,
-- 	a2.nume,
-- 	d2.den_dep,
-- 	a2.data_ang
-- FROM
-- 	angajati a,
-- 	angajati a2,
-- 	departamente d1,
-- 	departamente d2
-- WHERE
-- 	a.id_sef = a2.id_ang AND
-- 	a.id_dep = d1.id_dep AND
-- 	a2.id_dep = d2.id_dep AND
-- 	a2.nume != 'KING' AND
-- 	a.salariu > a2.salariu AND
-- 	a.nume != 'SCOTT';

-- SELECT
-- 	a.nume,
-- 	d1.den_dep,
-- 	a.data_ang,
-- 	a2.nume,
-- 	d2.den_dep,
-- 	a2.data_ang
-- FROM
-- 	angajati a
-- 	INNER JOIN departamente d1
-- 		ON a.id_dep = d1.id_dep,
-- 	angajati a2
-- 	INNER JOIN departamente d2
-- 		ON a2.id_dep = d2.id_dep
-- WHERE
-- 	a.id_sef = a2.id_ang AND
-- 	a2.nume != 'KING' AND
-- 	a.salariu > a2.salariu AND
-- 	a.nume != 'SCOTT';


-- SELECT
-- 	a.nume,
-- 	d1.den_dep,
-- 	a.data_ang,
-- 	a2.nume,
-- 	d2.den_dep,
-- 	a2.data_ang
-- FROM
-- 	departamente d1,
-- 	departamente d2,
-- 	angajati a
-- 	NATURAL JOIN departamente,
-- 	angajati a2
-- 	NATURAL JOIN departamente
-- WHERE
-- 	a.id_sef = a2.id_ang AND
-- 	a2.nume != 'KING' AND
-- 	a.salariu > a2.salariu AND
-- 	a.nume != 'SCOTT';

SELECT
	a.nume,
	d1.den_dep,
	a.data_ang,
	a2.nume,
	d2.den_dep,
	a2.data_ang
FROM
	angajati a
	INNER JOIN departamente d1
		ON a.id_dep = d1.id_dep,
	angajati a2
	INNER JOIN departamente d2
		ON a2.id_dep = d2.id_dep
WHERE
	a.id_sef = a2.id_ang AND
	a2.nume != 'KING' AND
	a.salariu > a2.salariu AND
	a.nume != 'SCOTT';



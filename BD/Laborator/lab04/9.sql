SELECT
	a.id_ang ecuson,
	a.nume,
	a.data_ang AS "Data Angajarii",
	a.salariu
FROM angajati a
WHERE id_dep = 10;
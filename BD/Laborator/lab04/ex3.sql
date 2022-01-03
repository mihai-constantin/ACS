set verify off;

accept id_dep char prompt 'Introduceti id_dep: '

SELECT
	id_ang ||'-'|| nume angajat,
	functie,
	(salariu + nvl(comision, 0)) * 12 AS "Venit anual"
FROM angajati
WHERE
	functie = 'MANAGER' AND
	id_dep = &id_dep;

undefine id_dep
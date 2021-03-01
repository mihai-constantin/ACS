set verify off;

accept id_dep1 char prompt 'Introduceti id_dep1: '
accept id_dep2 char prompt 'Introduceti id_dep2: '

SELECT
	id_ang ||'-'|| nume angajat,
	functie,
	salariu,
	data_ang,
	id_dep
FROM angajati
WHERE
	(data_ang BETWEEN '1-JAN-1981' AND '31-DEC-1981') AND
	(id_dep = &id_dep1 OR id_dep = &id_dep2);

undefine id_dep1
undefine id_dep2
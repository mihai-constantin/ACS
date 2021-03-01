define procent_prima = 0.15
define id_dep = 20

SELECT nume, salariu, salariu * &procent_prima prima
	FROM angajati
	WHERE id_dep = &id_dep;

undefine procent_prima
undefine id_dep
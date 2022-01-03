accept nr_departament char prompt 'Introduceti numarul departamentului: '
accept venit_mediu_anual char prompt 'Venit mediu anual: '

DEFINE venit_anual = salariu * 12 venit_anual + nvl(comision, 0)

select nume, functie, data_ang, id_dep, &venit_anual
	from angajati
	where id_dep = &nr_departament and &venit_anual > &venit_mediu_anual;

undefine nr_departament
undefine venit_mediu_anual
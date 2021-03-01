accept nr_departament char prompt 'Introduceti numarul departamentului: '

select id_dep, &&salariu_maxim_dep salariu_maxim_dep, id_ang, nume, salariu
	from angajati
	where id_dep = &nr_departament and salariu > (&salariu_maxim_dep / 2);
set verify off
accept nr_departament char prompt 'Introduceti numarul departamentului: '

select id_dep, &1 salariu_maxim_dep, id_ang, nume, salariu
	from angajati
	where id_dep = &nr_departament and salariu > (&1 / 2);

undefine nr_departament

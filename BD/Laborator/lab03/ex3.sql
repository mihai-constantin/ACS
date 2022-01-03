select id_dep, &1 salariu_maxim_dep, id_ang, nume, salariu
	from angajati
	where id_dep = &2 and salariu > (&1 / 2);
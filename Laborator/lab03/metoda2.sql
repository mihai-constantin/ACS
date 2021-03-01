select nume, functie, data_ang, id_dep, (salariu * 12 + nvl(comision, 0)) venit_anual
	from angajati
	where id_dep = &id_dep and (salariu * 12 + nvl(comision, 0)) > &venit_mediu_anual;
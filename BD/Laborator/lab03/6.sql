SELECT id_ang, nume, functie, data_ang
	FROM angajati
	WHERE functie = '&1' and data_ang > '&2'
	ORDER BY data_ang;
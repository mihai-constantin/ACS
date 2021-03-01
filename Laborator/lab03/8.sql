accept id_ang char prompt 'Introduceti ecusonul angajatului: '
accept nume char prompt 'Introduceti numele angajatului: '
accept functie char prompt 'Introduceti functia angajatului: '
accept salariu char prompt 'Introduceti salariul angajatului: ' hide

INSERT INTO angajati(id_ang, nume, functie, salariu)
	VALUES(&id_ang, '&nume', '&functie', &salariu);


undefine id_ang
undefine functie
undefine nume
undefine salariu
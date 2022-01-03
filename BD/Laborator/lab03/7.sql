ACCEPT functie_ang char prompt 'Introduceti functia angajatului:'

SELECT nume, salariu, comision
	FROM angajati
	WHERE functie = '&functie_ang';

undefine functie_ang
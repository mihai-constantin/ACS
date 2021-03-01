set verify off;
SELECT id_ang, nume, functie, salariu 
	FROM angajati 
	WHERE id_sef=&id_sef; 
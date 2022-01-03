INSERT INTO angajati (id_angajat, nume, prenume, functie, id_sef, id_departament, data_angajarii) VALUES (4003, 'Pop', 'Alina', 'Analist', 1001, 20, '21-NOV-1995');

INSERT INTO angajati(id_angajat, nume, prenume, functie, id_sef, id_departament, data_angajarii) VALUES (4004, 'Pop', 'Catalin', 'Tester', 1001, 20, '01-JAN-1980');

INSERT INTO angajati(id_angajat, nume, prenume, functie, id_sef, id_departament, data_angajarii) VALUES (4005, 'Pop', 'Andrei', 'Manager', 1001, 20, '14-FEB-1995');


SELECT nume, prenume, data_angajarii, comision FROM angajati;

DELETE FROM angajati WHERE nume = 'Pop' AND prenume = 'Alina';

SELECT nume, prenume, data_angajarii, comision FROM angajati;

DELETE FROM angajati WHERE data_angajarii < '01-JAN-1985';

SELECT nume, prenume, data_angajarii, comision FROM angajati;

DELETE FROM angajati WHERE comision IS NULL;

SELECT nume, prenume, data_angajarii, comision FROM angajati;
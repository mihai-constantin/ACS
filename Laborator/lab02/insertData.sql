INSERT INTO grila_salariu VALUES(1, 1, 1000);
INSERT INTO grila_salariu VALUES (1, 1001, 2000);

INSERT INTO departamente VALUES(10, 'Proiectare Software', '3212121');
INSERT INTO departamente VALUES(20, 'Asigurarea Calitatii', '3212122');
INSERT INTO departamente VALUES(10, 'Resurse Umane', '3212123');
INSERT INTO departamente VALUES(30, 'Proiectare Software', '3212124');

INSERT INTO angajati(id_angajat, nume, prenume, functie) VALUES (1001, 'Ionescu', 'Ion', 'Director');
INSERT INTO angajati(nume, prenume, functie) VALUES('Ionescu', 'Ionel', 'Programator');
INSERT INTO angajati(id_angajat, nume, prenume, functie, id_sef, salariu, id_departament) VALUES(1002, 'Ionescu', 'Ionel', 'Programator', 1001, 1024, 10);

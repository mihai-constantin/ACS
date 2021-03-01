CREATE TABLE departamente
(
	id_departament NUMBER(2) NOT NULL,
	denumire_departament VARCHAR2(30),
	telefon VARCHAR2(10)
);

CREATE TABLE grila_salariu (grad NUMBER(2), nivel_inferior NUMBER, nivel_superior NUMBER);

CREATE TABLE angajati
(
	id_angajat NUMBER(4) NOT NULL,
	nume VARCHAR2(30),
	prenume VARCHAR2(30),
	functie VARCHAR2(20),
	id_sef NUMBER(4),
	data_angajarii DATE DEFAULT SYSDATE,
	salariu NUMBER(7,2) DEFAULT 2000,
	comision NUMBER(7, 2),
	id_departament NUMBER
);
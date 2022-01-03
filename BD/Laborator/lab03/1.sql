CREATE TABLE angajati(
	id_ang NUMBER(4),
	nume VARCHAR(20),
	functie VARCHAR2(9),
	id_sef NUMBER(4),
	DATA_ANG DATE,
	salariu number(7, 2),
	comision NUMBER(7, 2),
	id_dep NUMBER(2));

INSERT INTO angajati select * from emp;
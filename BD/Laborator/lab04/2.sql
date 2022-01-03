CREATE TABLE angajati AS
SELECT
	empno id_ang,
	ename nume,
	job functie,
	mgr id_sef,
	hiredate data_ang,
	sal salariu,
	comm comision,
	deptno id_dep
FROM emp;
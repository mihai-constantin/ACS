drop table t1;
drop table t2;

-- pas1: creare tabela t1 pentru a afla cati subordonati are fiecare angajat
create table t1
as
select
    sef.ename Nume_sef,
    sef.empno Id_sef,
    sef.deptno Departament_sef,
    sef.hiredate Data_ang_sef,
    (select count(*) from emp ang where ang.mgr = sef.empno) Nr_subordonati
from
    emp sef;
   
-- pas2: eliminam din t1 angajatii care nu au niciun subordonat, adica care nu sunt sefi
-- punem rezultatele in tabelul t2
create table t2
as
select * from t1
where
    Nr_subordonati > 0;

-- pas3: afisare cerere finala: subalternii lui BLAKE
select
	ang.ename Nume_Angajat,
	sef.ename Nume_Sef,
	dep_ang.dname Nume_Dep_Ang,
	dep_sef.dname Nume_Dep_Sef
from
	emp ang,
	emp sef,
	dept dep_ang,
	dept dep_sef
where
	dep_ang.deptno = ang.deptno and
	dep_sef.deptno = sef.deptno and
	ang.mgr = sef.empno and
	sef.empno = (select Id_sef
					from t2
					where Nr_subordonati = (select max(Nr_subordonati) from t2));
	
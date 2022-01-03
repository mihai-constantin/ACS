drop table t1;
drop table t2;
drop table t3;
-- Creati un view, denumit angajati_prima, care contine, pentru fiecare angajat: 
-- numele “Nume”, 
-- luna in care s-au angajat “Luna_ang” 
-- si prima.
-- Prima este acordata angajatilor din 
-- departamentul care are cei mai multi sefi, 
-- dupa urmatoarele criterii:
-- a. cei angajati in luna decembrie, 
-- 	care nu sunt manageri primesc: log in baza 2 de salariu + sqrt salariu
-- b. cei angajati in luna 
-- 	decembrie, care sunt manageri primesc: 
-- 	log in baza 3 de salariu + 10 
-- c. ceilalti primesc: 0.5 din salariu
-- Pentru testare, se va utiliza baza de date formata din tabelele EMP, DEPT si SALGRADE.

create table t1
as
select
    sef.ename Nume_sef,
    sef.deptno Departament_sef,
    sef.hiredate Data_ang_sef,
    (select count(*) from emp ang where ang.mgr = sef.empno) Nr_subordonati
from
    emp sef;
    
create table t2
as
select * from t1
where
    Nr_subordonati > 0;


select * from t2;

create table t3
as
select
	ang.Departament_sef Departament,
	count(ang.Nume_Sef) Nr_sefi
from
	t2 ang
group by
	ang.Departament_sef
order by
	ang.Departament_sef;

select * from t3;

select
	ang.ename Nume,
	ang.hiredate Data_ang,
	ang.job Functie_ang,
	extract (month from ang.hiredate) Luna_ang,
	case
		when extract(month from ang.hiredate) = 12 and ang.job != 'MANAGER' then log(2, ang.sal) + sqrt(ang.sal)
		when extract(month from ang.hiredate) = 12 and ang.job = 'MANAGER' then log(3, ang.sal) + 10
		else ang.sal * 0.5
	end PRIMA
from
	emp ang
where
	ang.deptno = (select
					Departament
				from
					t3
				where 
					Nr_sefi = (select max(Nr_sefi) from t3));


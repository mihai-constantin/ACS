-- Să se creeze tabela Statistica_Sefi, cu următoarele coloane:
-- - Nume_Sef
-- - Venit_Sef
-- - ​Nume_Departament_Subalterni​ (numele departamentului în care are subalterni) 
-- - Numar_Subalterni (numărul subalternilor pentru acest șef din ​dipartament​)
-- - Medie_Venit_Subalterni (media veniturilor subalternilor din acel departament)
-- Să se populeze tabela în conformitate cu aceste cerințe 
-- pentru fiecare șef din companie, persoană din tabela EMP 
-- care are minim un subaltern, care este din același departament cu minim un subaltern.
-- Pentru testare, se va utiliza baza de date formata din tabelele EMP, DEPT si SALGRADE.

drop table t1;
drop table t2;
drop table Statistica_Sefi;

create table t1
as
select
	ang.ename Nume_ang,
	ang.sal Sal_ang,
	ang.deptno Id_dep_ang,
	sef.ename Nume_sef
from
	emp ang,
	emp sef
where
	ang.mgr = sef.empno
order by 2;

create table t2
as
select
	ang.Nume_sef Nume_Sef,
	count(ang.Nume_ang) Numar_Subalterni,
	avg(ang.Sal_ang) Medie_Sal_ang,
	ang.Id_dep_ang Id_dep_ang
from
	t1 ang
group by
	ang.Nume_sef,
	ang.Id_dep_ang;

select * from t2;

create table Statistica_Sefi
as 
select
	sef.Nume_Sef Nume_Sef,
	ang.sal Venit_Sef,
	d.dname Nume_Departament_Subalterni,
	sef.Numar_Subalterni Numar_Subalterni,
	sef.Medie_Sal_ang Medie_Venit_Subalterni
from
	t2 sef,
	emp ang,
	dept d
where
	ang.ename = sef.Nume_Sef and
	d.deptno = sef.Id_dep_ang;

select * from Statistica_Sefi;

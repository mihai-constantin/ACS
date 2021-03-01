-- Sa se creeze o tabela, denumita PRIMII_VENITI cu 
-- toti angajatii care au venit in firma primii 
-- din departamentul lor. 
-- Structura tabelei este urmatoarea :
-- Nume_angajat, 
-- Den_departament, 
-- Data_angajare, 
-- Ani_vechime
-- Se vor lua in considerare doar departamentele 
-- unde primii veniti au o vechime de cel putin 39 de ani.
-- Vechimea se va calcula ca si numar natural.
-- Pentru testare, se va utiliza baza de 
-- date formata din tabelele EMP, DEPT si SALGRADE.

drop table t1;
drop table t2;
drop table t3;

create table t1
as
select
    d.deptno no_dept,
    e.empno id_ang,
    e.ename nume_ang,
    e.hiredate data_ang,
    extract (year from sysdate)  - extract(year from e.hiredate) vechime
from
    emp e,
    dept d
where
    d.deptno = e.deptno
order by
    d.deptno;
    
-- select * from t1;

create table t2
as
select
    *
from 
    t1
where 
    vechime >= 39;
    
create table t3
as
select
    ang.no_dept nr_departament,
    min(ang.data_ang) data_minima
from 
    t2 ang
group by
    ang.no_dept
order by
    ang.no_dept;
    
-- select * from t3;
    
create table PRIMII_VENITI
as
select
    e.ename Nume_angajat,
    d.dname Denumire_departament,
    e.hiredate Data_angajare,
    extract(year from sysdate) - extract(year from e.hiredate) Vechime
from
    emp e,
    dept d
where
	e.deptno = d.deptno and
    (e.deptno, e.hiredate) in (select
                                    ang.no_dept,
                                    min(ang.data_ang)
                                from 
                                    t2 ang
                                group by
                                    ang.no_dept)
order by
	e.deptno;
	
	
select * from PRIMII_VENITI;
	

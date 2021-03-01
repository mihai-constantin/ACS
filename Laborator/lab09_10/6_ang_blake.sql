-- Sa se creeze o tabela denumita ANG_BLAKE 
-- care sa contina toti angajatii din departamentul 
-- sefului cu cei mai multi subordonati. 
-- Structura tabelei este urmatoarea: 
-- Nume_angajat, 
-- Den_departament, 
-- An_angajare, 
-- Venit, 
-- Ani_vechime
-- Vechimea se va calcula ca si numar natural.
-- Pentru testare, se va utiliza baza 
-- de date formata din tabelele EMP, DEPT si SALGRADE.

drop table t1;
drop table t2;
drop table ANG_BLAKE;

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

create table ANG_BLAKE
as
select 
    e.ename Nume_ang,
    d.dname Den_dep,
    extract(year from e.hiredate) An_ang,
    e.sal * 12 + nvl(e.comm, 0) Venit,
    extract(year from sysdate) - extract(year from e.hiredate) Ani_vechime
from
    emp e,
    dept d
where
    e.deptno = d.deptno and
    e.deptno = (select 
                    Departament_sef 
                from 
                    t2 
                where 
                    Nr_subordonati = (select max(Nr_subordonati) from t2));
                    
select * from ANG_BLAKE;

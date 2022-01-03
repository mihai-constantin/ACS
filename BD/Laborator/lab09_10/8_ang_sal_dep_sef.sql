-- Creati o tabela care contine, pentru angajatii din 
-- departamentul cu numarul maxim de angajati cu salariul mai mic 
-- decat media salariilor din departamentul 
-- unde lucreaza seful lor: 
-- id-ul angajatului, 
-- numele angajatului cu prima litera mare si restul mici “Nume” 
-- si departamentul din care face parte angajatul, 
-- concatentat cu functia lui “Den_dep_job”. 
-- Adaugati o constrangere de integritate 
-- de tip primary key pe id-ul angajatului.

drop table t1;
drop table t2;
drop table t3;
drop table t4;
drop table t5;
drop table salarii_medii;

-- calculam salariile medii pe fiecare departament
create table salarii_medii
as
select
    e.deptno ID_dep,
    avg(e.sal) Salariu_mediu
from
    emp e
group by
    e.deptno
order by
    e.deptno;
    
select * from salarii_medii;

create table t1
as
select
    sef.empno ID_sef,
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
    *
from
    t2 sef,
    salarii_medii sm
where
    sef.Departament_sef = sm.ID_dep;
    
select * from t3;

create table t4
as
select
    ang.deptno ID_dep_ang,
    ang.empno ID_ang,
    ang.ename Nume_ang,
    ang.sal Sal_ang,
    sef.ID_sef ID_sef,
    sef.Nume_sef Nume_sef
from
    emp ang,
    t3 sef
where
    ang.mgr = sef.ID_sef and
    ang.sal < sef.Salariu_mediu
order by
    1;
    
select * from t4;

create table t5
as
select
    ang.ID_dep_ang ID_dep,
    count(ang.ID_ang) Numar_angajati
from
    t4 ang
group by
    ang.ID_dep_ang
order by
    ang.ID_dep_ang;

select * from t5;

create table ANG
as
select
    e.empno ID_ang,
    concat(substr(e.ename, 0, 1), lower(substr(e.ename, 2))) Nume,
    concat(concat(e.deptno, ' '), e.job) Den_dep_job
from
    emp e
where
    e.deptno = (select
                    ID_dep Departament
                from t5
                where Numar_angajati = (select max(Numar_angajati) from t5));
                
select * from ANG;

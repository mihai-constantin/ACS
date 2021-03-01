-- Sa se creeze tabela SUBALTERNI cu urmatoarea structura:
-- ID_sef, Data_ang_sef, Sal_sef, ID_sub, Data_ang_sub, Sal_sub
-- In aceasta tabela se vor insera date pentru sefi si subalternii lor, 
-- dar numai pentru sefii si subalternii care au venit in companie 
-- in anul in care s-a angajat cel mai recent sef din departament.
-- Pentru testare, se va utiliza baza de date 
-- formata din tabelele EMP, DEPT si SALGRADE.

drop table t1;
drop table t2;
drop table t3;
drop table t4;

select * from emp;

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

-- iau din t2 cel mai recent angajat per departament
create table t3
as
select
    subordonati.Departament_sef Departament_sef,
    -- subordonati.Nume_sef,
    -- subordonati.Departament_sef,
    -- subordonati.Nr_subordonati,
    max(subordonati.Data_ang_sef) Data_minima
from
    t2 subordonati
group by
    subordonati.Departament_sef
order by
    subordonati.Departament_sef;

select * from t3;

create table t4
as
select
    *
from 
    emp ang,
    t3 date_minime
where
    ang.deptno = date_minime.Departament_sef and
    extract(year from ang.hiredate) = extract(year from date_minime.Data_minima)
order by
    date_minime.Departament_sef;

select * from t4;

select
    sef.deptno ID_dep_sef,
    sef.empno ID_sef,
    sef.hiredate Data_ang_sef,
    sef.sal Sal_sef,
    ang.empno ID_sub,
    ang.hiredate Data_ang_sub,
    ang.sal Sal_sub
from
    t4 sef,
    t4 ang
where
    ang.mgr = sef.empno and
    ang.deptno = sef.deptno
order by 1;
    

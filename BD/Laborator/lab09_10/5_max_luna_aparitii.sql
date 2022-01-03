-- Creati o tabela care contine, 
-- pentru angajatii din departamentul cu cei mai multi angajati 
-- care s-au angajat in aceeasi luna: 
-- id-ul angajatului, 
-- numele “Nume”,
-- numele departamentului din care fac parte, 
-- cu prima litera mare si restul mici, 
-- “Den_dep” si luna angajarii “Luna_ang”.
-- Adaugati o constrangere 
-- de integritate de tip primary key pe id-ul angajatului.

drop table t1;
drop table t2;

create table t1
as
select 
    extract(month from ang.hiredate) luna,
    ang.deptno nr_dep,
    count(empno) nr_ang
from 
    emp ang
group by
    extract(month from ang.hiredate),
    ang.deptno
order by 
    ang.deptno;
    
select * from t1;
    
-- select
--     ang.nr_dep
-- from
--     t1 ang
-- where
--     ang.nr_ang = (select max(nr_ang) from t1);
    
create table t2
as
select
    e.empno Id_ang,
    e.ename Nume_ang,
    d.dname Den_dep,
    extract(month from e.hiredate) Luna_ang
from
    emp e,
    dept d
where
    d.deptno = e.deptno and
    e.deptno = (select
                        ang.nr_dep
                    from
                        t1 ang
                    where
                        ang.nr_ang = (select max(nr_ang) from t1));
                        
select * from t2;

alter table t2 add constraint pk_col_id_ang primary key (id_ang);


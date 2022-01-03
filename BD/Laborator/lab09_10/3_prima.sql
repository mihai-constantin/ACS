-- Sa se creeze un tabel numit PRIMA in care se vor 
-- stoca angajatii care primesc prima. 
-- Prima se acorda angajatilor care nu primesc comision 
-- si s-au angajat inaintea presedintelui, astfel: 
-- - salariul minim din firma, daca salariatul are gradul 1 in grila
-- - media corespunzatoare gradului, 
-- daca are gradul 2 sau 3 (media se calculeaza pe baza "losal" si "hisal")
-- - salariul mediu din firma rotunjit la doua zecimale, daca are gradul 4
-- - jumatate din salariul maxim din firma, daca are gradul 5
-- Tabelul va avea urmatoarele coloane: 
-- NUME (nume angajat), 
-- GRAD (gradatia salariala a angajatului), 
-- PRIMA, 
-- ID_DEP (id-ul departamentului in care lucreaza angajatul), 
-- COMISION iar inregistrarile cu care 
-- este populat apar ordonate crescator functie de valoarea primei.
-- Scriptul va contine la final si instructiunea 
-- de afisare a tuturor inregistrarilor 
-- din tabela nou creata (select * from prima;)
-- Pentru testare, se va utiliza baza de date 
-- formata din tabelele EMP, DEPT si SALGRADE.

drop table data_ang_presedinte;
drop table t1;
drop table PRIMA;

-- determin anul in care s-a angajat presedintele
create table data_ang_presedinte
as
select 
    hiredate data_ang_king
from
    emp
where
    job = 'PRESIDENT';
    
select * from data_ang_presedinte;

create table t1
as
select *
from 
    emp,
    salgrade s
where 
    nvl(comm, 0) = 0 and 
    hiredate < (select * from data_ang_presedinte) and
    sal >= s.losal and sal <= s.hisal;
    
select * from t1;

create table PRIMA
as
select
    ang.ename NUME,
    ang.grade GRAD,
    case ang.grade
        when 1 then (select min(sal) from emp)
        when 2 then (ang.losal + ang.hisal) / 2
        when 3 then (ang.losal + ang.hisal) / 2
        when 4 then round((select avg(sal) from emp), 2)
        when 5 then (select max(sal) from emp) / 2
    end PRIMA,
    ang.deptno ID_DEP,
    ang.comm COMISION
from
    t1 ang
order by
    PRIMA;
    
select * from PRIMA;

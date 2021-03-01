
-- ex 1
-- Sa se faca o lista toti angajatii care primesc o prima de 10% din salariu. 
-- Prima primesc numai angajatii care nu au primit comision si au venit 
-- in companie in primele 6 luni ale anului in care s-a angajat 
-- presedintele companiei.
-- Antetul listei este:
-- Nume_Presedinte, 
-- Data_ang_pres, 
-- Nume_ang, 
-- Data_ang, 
-- Salariu_ang, 
-- Comision, 
-- Prima

-- Se vor prezenta doua scripturi (metode de rezolvare) diferite.
-- Pentru testare, se va utiliza baza de date 
-- formata din tabelele EMP, DEPT si SALGRADE.

-- metoda 1

-- selectam anul in care a venit presedintele companiei

-- select
-- 	sef.ename Nume_Presedinte,
-- 	sef.hiredate Data_ang_pres,
-- 	ang.ename Nume_ang,
-- 	ang.hiredate Data_ang,
-- 	ang.sal Salariu_ang,
-- 	ang.comm Comision,
-- 	ang.sal * 0.1 Prima
-- from
-- 	emp ang,
-- 	emp sef
-- where
-- 	sef.empno = ang.mgr and
-- 	nvl(ang.comm, 0) = 0 and
-- 	extract(year from ang.hiredate) = (select
-- 									extract(year from e.hiredate)
-- 									from
-- 										emp e
-- 									where
-- 										e.job = 'PRESIDENT') and
-- 	extract(month from ang.hiredate) <= 6;

-- ex 2

-- Selectati angajatii care s-au angajat in 
-- ultimele 4 luni ale anului, intre anii 1981 si 1983, 
-- nu primesc comision si lucreaza ca analisti . 
-- Se va afisa si data semnarii contractului de angajare, 
-- stiind ca aceasta a fost urmatoarea zi de luni dupa 
-- data angajarii. 
-- Se va afisa numele concatentat cu functia (ex. "FORD is ANALYST"), 
-- functia, salariul anual (concatenat cu sirul 'USD'), 
-- comisionul (daca e nul se va afisa 0), 
-- data semnarii contractului 
-- (in format cu luna si anul complet, ex.'24-DECEMBER-1982') 
-- si se va ordona alfabetic dupa nume. 
-- Antetul listei este 
-- nume_func, 
-- salariu_anual, 
-- comision, 
-- data_contract.
-- Se vor prezenta doua scripturi (metode de rezolvare) diferite. 
-- Pentru testare, se va utiliza baza de date formata 
-- din tabelele EMP, DEPT si SALGRADE.

-- alter session set NLS_DATE_FORMAT='DD-MONTH-YYYY';
-- select 
-- 	concat(concat(ang.ename, ' is '), ang.job)  nume_func,
-- 	concat((ang.sal + nvl(ang.comm, 0)) * 12, ' USD') salariu_anual,
-- 	nvl(ang.comm, 0) comision,
-- 	next_day(ang.hiredate, 'MONDAY') data_contract
-- from 
-- 	emp ang
-- where
-- 	extract(month from ang.hiredate) >= 9 and
-- 	extract(year from ang.hiredate) >= 1981 and
-- 	extract(year from ang.hiredate) <= 1983 and
-- 	nvl(ang.comm, 0) = 0 and
-- 	ang.job = 'ANALYST';


-- CREATE TABLE SUBALTERNI AS
-- SELECT
-- m.empno "ID_sef", m.hiredate "Data_ang_sef", m.sal "Sal_sef",
-- e.empno "ID_sub", e.hiredate "Data_ang_sub", e.sal "Sal_sub"
-- FROM emp e INNER JOIN emp m ON e.mgr = m.empno
-- INNER JOIN dept d
-- ON e.deptno = d.deptno
-- WHERE e.deptno = m.deptno AND extract(year from e.hiredate) = extract(year from m.hiredate)
-- AND extract(year from e.hiredate) = extract(year from (SELECT hiredate
-- FROM emp e1
-- WHERE e1.deptno = e.deptno AND e1.hiredate >= ALL(SELECT hiredate
-- FROM emp WHERE deptno =
-- e1.deptno)));


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

-- CREATE TABLE Statistica_Sefi( Nume_Sef,
-- Venit_Sef, Grila_Salariala_Subalterni, Numar_Subalterni, Medie_Venit_Subalterni
-- )
-- AS SELECT
-- m.ename,
-- m.sal + nvl(m.comm, 0), g.grade, count(e.ename),
-- avg(e.sal + nvl(e.comm, 0)) FROM emp e INNER JOIN emp m
-- ON e.mgr = m.empno
-- INNER JOIN salgrade g
-- ON e.sal BETWEEN g.losal AND g.hisal
-- GROUP BY m.ename, e.mgr, m.sal + nvl(m.comm, 0), g.grade HAVING
-- e.mgr in (SELECT mgr FROM emp
-- GROUP BY mgr
-- HAVING count(ename) >= 1 AND mgr IS NOT NULL
-- )
-- AND count(e.ename) >= 1;


-- Sa se scrie o cerere  SQL*Plus  care face o 
-- lista cu departamentul in care s-au 
-- facut cele mai multe angajari intr-un an. 
-- Lista va contine denumirea 
-- de departament, anul in care s-au 
-- facut cele mai multe angajari in 
-- departamentul respectiv si numarul de angajari.

-- Antetul listei este urmatorul :              
-- DEN_DEP        AN       NR_ANG

-- Pentru testare, se va utiliza baza
--  de date formata din tabelele EMP, DEPT si SALGRADE.

-- drop table t1;
-- drop table t2;

-- create table t1
-- as
-- select
-- 	e.deptno Id_dep,
-- 	e.ename Nume_ang,
-- 	extract (year from e.hiredate) An_ang
-- from
-- 	emp e
-- order by
-- 	e.deptno;

-- select * from t1;

-- create table t2
-- as
-- select
-- 	ang.An_ang An_ang,
-- 	ang.Id_dep Id_dep,
-- 	count(ang.Nume_ang) Nr_angajati
-- from
-- 	t1 ang
-- group by
-- 	ang.Id_dep,
-- 	ang.An_ang
-- order by 
-- 	ang.Id_dep;


-- select * from t2;

-- select
-- 	d.dname Den_departament,
-- 	t2.An_ang AN,
-- 	t2.Nr_angajati Nr_angajati
-- from 
-- 	t2,
-- 	dept d
-- where
-- 	d.deptno = Id_dep and
-- 	Nr_angajati = (select max(Nr_angajati) from t2);


-- Sa se scrie o cerere SQL*Plus care face o 
-- lista cu subalternii sefului care are cei mai multi subalterni.
-- Antetul Listei:
-- - Nume_Angajat
-- - Nume_Sef
-- - Nume_Dep_Ang
-- - Nume_Dep_Sef
-- Seful unui angajat este specificat prin coloana MGR.
-- Pentru testare, se va utiliza baza de date 
-- formata din tabelele EMP, DEPT si SALGRADE.


drop table t1;
drop table t2;

-- pas1: creare tabela pentru a afla cati subordonati are fiecare angajat
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
   
-- pas2: eliminam din t1, angajatii care nu au niciun subordonat, adica care nu sunt sefi
create table t2
as
select * from t1
where
    Nr_subordonati > 0;

-- pas3: afisare tabela finala: subalternii lui BLAKE 
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

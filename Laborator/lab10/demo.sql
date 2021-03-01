-- ex 1

-- create table exemplu
-- (
-- 	data_implicita date default sysdate,
-- 	numar_implicit number(7, 2) default 7.24,
-- 	string_implicit varchar2(5) default 'test',
-- 	operator varchar2(10) default user
-- );

-- select table_name, column_name, data_default
-- from user_tab_columns
-- where table_name = 'EXEMPLU';

-- ex 2
-- create table dept_20
-- as
-- select 	id_dep, 
-- 		nume, 
-- 		data_ang, 
-- 		salariu + nvl(comision, 0) venit
-- from angajati
-- where id_dep = 20;

-- ex 4
-- create table functii
-- (
-- 	cod number(2) constraint pk_cod primary key,
-- 	functie varchar2(20),
-- 	data_vigoare date default sysdate
-- );

-- select sef.ename "Nume_sef",
--    		 (SELECT COUNT (*)
--    		 FROM emp ang
--     		WHERE sef.empno = ang.mgr) "Angajati_sef"
-- FROM emp sef;


-- SELECT 	a.ename,
-- 		a.hiredate
-- from 	emp a, 
-- 		dept d,
-- 		(select
-- 			deptno,
-- 			min(hiredate) min_hiredate
-- 			from emp
-- 			group by deptno) b
-- where a.hiredate = b.min_hiredate
-- order by a.ename;
-- -- where 
-- -- 	a.deptno = d.deptno and 
-- -- 	EXTRACT(YEAR FROM sysdate) - EXTRACT(YEAR from a.hiredate) >= 39 and 
-- -- 	a.hiredate = (select MIN(a.hiredate) from emp group by deptno);






-- create table
-- (
-- 	Nume_Sef,
-- 	Venit_Sef,
-- 	Nume_Departament_Subalterni,
-- 	Numar_Subalterni,
-- 	Medie_Venit_Subalterni
-- )
-- as
	
-- select a.ename Nume_sef,
-- 		(select count(*)
-- 			from emp b
-- 			where a.empno = b.mgr) Numar_Subalterni
-- from ename a;


-- create table table1
-- (
-- 	Nume_Sef,
-- 	Numar_Subalterni
-- )
-- as
-- select
-- 	a.ename Nume_sef,
--    	(select count(*)
--    		from emp b
--     	where a.empno = b.mgr) Numar_Subalterni
-- from emp a;

-- create table table2
-- (
-- 	Nume_Sef,
-- 	Numar_Subalterni
-- )
-- as
-- select
-- 	a.Nume_Sef Nume_sef,
-- 	a.Numar_Subalterni Numar_Subalterni
-- from table1 a
-- where a.Numar_Subalterni > 0;


create table Statistica_Sefi
(
	Nume_Sef,
	Venit_Sef,
	Nume_Departament_Subalterni,
	Numar_Subalterni,
	Medie_Venit_Subalterni
)
as
select
	a.Nume_Sef Nume_sef,
	b.sal * 12 + nvl(b.comm, 0) Venit_Sef,
	d.deptno Nume_Departament_Subalterni,
	a.Numar_Subalterni Numar_Subalterni,
	select () Medie_Venit_Subalterni
from table2 a,
	 emp b,
	 dept d
where a.Nume_Sef = b.ename and
	  b.deptno = d.deptno;

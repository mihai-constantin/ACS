-- Sa se selecteze angajatii care au cele mai mari doua venituri 
-- din departamentul cu cei mai multi angajati.  
-- Se va afisa, pentru fiecare angajat, o lista cu antetul:

-- Nume, Den_departament, Venit

-- Pentru testare, se va utiliza baza de date 
-- formata din tabelele EMP, DEPT si SALGRADE.


-- departamentul cu cei mai multi angajati
drop table t1;
drop table t2;

create table t1
as
select
	e.ename Nume_ang,
	d.dname Den_dep,
	e.deptno Nr_dep
from
	emp e,
	dept d
where
	e.deptno = d.deptno
order by
	e.deptno;

create table t2
as
select
	ang.Nr_dep Nr_dep,
	count(ang.Nume_ang) Nr_angajati
from
	t1 ang
group by
	ang.Nr_dep
order by
	ang.Nr_dep;

select * from t2;

select 
	e.ename Nume,
	d.dname Den_departament,
	e.sal + nvl(e.comm, 0) Venit
from
	emp e,
	dept d
where
	e.deptno = d.deptno and
	e.deptno = (select Nr_dep
				from t2
				where Nr_angajati = (select max(Nr_angajati) from t2))
order by 3 DESC
fetch first 2 rows only;


-- Sa se selecteze angajatii care au cele mai mari trei venituri  
-- din departamentul angajatului cu cei mai multi subordonati direct.

-- Nume, Den_departament, Venit

-- Seful unui angajat este specificat prin coloana MGR.

-- Pentru testare, se va utiliza baza de 
-- date formata din tabelele EMP, DEPT si SALGRADE.

drop table t1;
drop table t2;

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

select
	e.ename Nume,
	d.dname Denumire_dep,
	e.sal  + nvl(e.comm, 0) Venit
from
	emp e,
	dept d
where
	e.deptno = d.deptno and
	e.deptno = (select
					Departament_sef
				from
					t2
				where Nr_subordonati =  (select max(Nr_subordonati) from t2))
order by 3 DESC
fetch first 3 rows only;


-- Sa se scrie o cerere SQL*Plus care face o lista 
-- cu toti angajatii din companie,locatia 
-- departamenului lor si numarul de 
-- angajati din locatia respectiva. 
-- Lista va contine numai angajatii 
-- din locatiile care au un numar 
-- de angajati multiplu de 3.  Antetul Listei:

-- - Nume_Angajat 
-- - Locatie_Departament
-- - Numar_Angajati_Loc

-- Pentru testare, se va utiliza baza de date 
-- formata din tabelele EMP, DEPT si SALGRADE.

drop table t1;
drop table t2;
drop table t3;
	
create table t1
as
select
	e.ename Nume_ang,
	e.deptno Nr_dep,
	d.dname Den_dep,
	d.loc Locatie_dep
from
	emp e,
	dept d
where
	e.deptno = d.deptno;

select * from t1;

create table t2
as
select
	ang.Locatie_dep Locatie,
	count(ang.Nume_ang) Nr_angajati
from
	t1 ang
group by
	ang.Locatie_dep;	

select * from t2;

create table t3
as
select * 
from 
	t2 
where 
	mod(Nr_angajati, 3) = 0;

select * from t3;

select
	ang.ename Nume_ang,
	locatii.Locatie Locatie_dep,
	locatii.Nr_angajati Nr_angajati_Loc
from
	t3 locatii,
	emp ang,
	dept d
where
	ang.deptno = d.deptno and
	d.loc = locatii.Locatie;

-- Sa se scrie o cerere Oracle SQL prin care 
-- se acorda o prima angajatilor care au grad salarial 
-- mai mic decat cel mai mic grad salarial al 
-- angajatilor cu functia MANAGER si 
-- lucreaza in departamentele cu cei 
-- mai putini angajati veniti in firma in anul 1981.

-- Prima se calculateaza ca an_ang * sal_max_dept / 1000.
-- Unde:

-- - an_ang este anul in care a venit angajatul in firma
-- - sal_max_dept este salariul maxim pentru departamentului angajatului


-- Nume_Angajat | Nume_Deptartament | Grad_Salarial | Venit_Lunar | Prima

drop table t1;
drop table t2;
drop table t3;
drop table t4;
drop table nr_departamente_1981;
drop table salarii_maxime;

create table t1
as
select
	e.ename Nume_ang,
	e.deptno Id_dep_ang,
	d.dname Den_dep_ang
from
	emp e,
	dept d
where
	e.deptno = d.deptno and
	extract (year from e.hiredate) = 1981;

select * from t1;

create table t2
as
select 
	ang.Id_dep_ang Id_dep_ang,
	count(ang.Nume_ang) Nr_ang
from
	t1 ang
group by
	ang.Id_dep_ang;

select * from t2;

create table nr_departamente_1981
as
select
	Id_dep_ang
from t2
where Nr_ang = (select min(Nr_ang)
				from
					t2);


select * from nr_departamente_1981;


create table t3
as
select
	*
from
	emp,
	salgrade
where
	deptno in (select * from nr_departamente_1981) and
	job = 'MANAGER' and
	sal >= losal and sal <= hisal
order by
	deptno;

select * from t3;

create table t4
as
select 
	*
from 
	emp,
	salgrade
where
	sal >= losal and sal <= hisal and
	grade < (select
				min(grade)
			from
			t3);

select * from t4;

-- calculam salariul maxim per departament
create table salarii_maxime
as
select
	e.deptno Id_dep,
	max(e.sal) Salariu_maxim
from
	emp e 
group by
	e.deptno;

select * from salarii_maxime;

select
	ang.ename Nume_Angajat,
	d.dname Nume_Deptartament,
	ang.grade Grad_Salarial,
	ang.sal + nvl(ang.comm, 0) Venit_Lunar,
	(extract(year from ang.hiredate) * sm.Salariu_maxim) / 1000 Prima
from
	t4 ang,
	dept d,
	salarii_maxime sm
where
	ang.deptno = d.deptno and
	sm.Id_dep = ang.deptno;

-- Afisati toti angajatii din departamentul cu 
-- cei mai multi angajati care nu s-au angajat 
-- in lunile de iarna (Dec, Ian si Febr). 
-- Se va afisa 
-- denumire departament, 
-- nume angajat, 
-- data angajarii, 
-- ordonati dupa data angajarii crescator.

-- Antetul listei este den_dep, nume, data_ang.

-- Pentru testare, se va utiliza baza de 
-- date formata din tabelele EMP, DEPT si SALGRADE.


drop table t1;
drop table t2;

create table t1
as
select
	e.ename Nume_ang,
	e.deptno Id_dep,
	extract (month from e.hiredate) Luna_ang,
	e.hiredate Data_ang
from
	emp e
where
	extract(month from e.hiredate) != 12 and
	extract(month from e.hiredate) != 1 and
	extract(month from e.hiredate) != 2;

select * from t1;

create table t2
as
select
	ang.Id_dep Id_dep,
	count(ang.Nume_ang) Nr_angajati
from
	t1 ang
group by
	ang.Id_dep
order by
	ang.Id_dep;


select * from t2;

select
	d.dname Den_departament,
	ang.Nume_ang Nume_ang,
	ang.Data_ang Data_ang
from
	t1 ang,
	dept d
where
	d.deptno = ang.Id_dep and
	ang.Id_dep = (select 
						Id_dep 
					from 
						t2 
					where 
						Nr_angajati = (select max(Nr_angajati) from t2))
order by 3 asc;


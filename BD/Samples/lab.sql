select * from emp
	where emp.job = 'ANALYST';

-- Sa se faca o lista toti angajatii care primesc un bonus de 10% din salariu. 
-- Bonusul se acorda doar angajatilor care fac parte din acelasi departament cu presedintele companiei, 
-- au salariul mai mic decat jumatate din salariul lui, nu au primit comision si au venit in companie in acelasi an cu el.

-- Antetul listei este:

-- Nume_Pres, An_ang_pres, Salariu_pres, Nume_ang,  Data_ang, Salariu_ang, Bonus

-- Se vor prezenta doua scripturi (metode de rezolvare) diferite.

-- Pentru testare, se va utiliza baza de date formata din tabelele EMP, DEPT si SALGRADE.

-- metoda 1
-- select
-- 	e1.ename Nume_Pres,
-- 	extract(year from e1.hiredate) An_ang_pres,
-- 	e1.sal Salariu_pres,
-- 	e2.ename Nume_ang,
-- 	e2.hiredate Data_ang,
-- 	e2.sal Salariu_ang,
-- 	0.1 * e2.sal Bonus
-- from
-- 	emp e1,
-- 	emp e2
-- where
-- 	e1.job = 'PRESIDENT' and
-- 	e1.deptno = e2.deptno and
-- 	e2.sal < e1.sal/2 and
-- 	(e2.comm is null or e2.comm = 0) and
-- 	extract(year from e2.hiredate) != extract(year from e1.hiredate);

-- metoda 2

-- Pentru toti angajatii care NU lucreaza intr-un departament introdus de la tastatura 
-- sau (care s-au angajat intr-un an par si a caror functie incepe cu litera a), afisati:

-- - coloana "Nume ascuns", care pentru fiecare litera din nume afisaza caracterul * (de exemplu: Iulia = ***)

-- - coloana “Lungime nume” care contine numarul de caractere al numelui,

-- - coloana "Calcul Luna" care contine prima zi din luna in care s-au angajat,

-- - coloana "Calcul An" care contine prima zi din anul angajarii,

-- - data angajarii.

-- Hint: Functia TRUNC poate fi aplicata si pe date calendaristice.

-- Cerinta trebuie rezolvata prin doua metode (scripturi) diferite.

-- Pentru testare, se va utiliza baza de date formata din tabelele EMP, DEPT si SALGRADE.

-- accept id_dep char prompt 'Introduceti id_dep: '

-- select
-- 	e1.ename "Nume ascuns",
-- 	length(e1.ename) "Lungime nume",
-- 	last_day(extract(month from e1.hiredate)) "Calcul Luna",
-- 	last_day(extract(year from e1.hiredate)) "Calcul An",
-- 	e1.hiredate "Data_ang"
-- from 
-- 	emp e1
-- where
-- 	e1.deptno != &id_dep or
-- 	mod(extract(year from e1.hiredate), 2) = 0 or
-- 	e1.job like 'A%';

-- undefine id_dep

-- Afisati, pentru angajatii care : (fac parte din departamentele 10 sau 20 
-- si care s-au angajat dupa anul 1980) sau (a caror functie contine 5 caractere), urmatoarea lista:

-- - numele,

-- - functia,

-- - data angajarii,

-- - caracterul din mijlocul numelui lor “Caracter Mijloc”,

-- - ultimele 3 caractere din functie “Ultimele 3”,

-- - ultima zi din luna in care s-au angajat “Ultima Zi Luna”.

-- Cerinta trebuie rezolvata prin doua metode (scripturi) diferite.

-- Pentru testare, se va utiliza baza de date formata din tabelele EMP, DEPT si SALGRADE.


-- select 
-- 	e.ename nume,
-- 	e.job functie,
-- 	e.hiredate Data_ang,
-- 	SUBSTR(e.ename, length(e.ename), 1) as "char mijloc",
-- 	SUBSTR(e.job, length(e.job)-2, 3) "Ultimele 3",
-- 	last_day(e.hiredate) "Ultima zi luna"
-- from 
-- 	emp e
-- where
-- 	((e.deptno = 10 or e.deptno = 20) and
-- 	extract(year from e.hiredate) >= 1980) or
-- 	length(e.job) = 5;


-- Selectati angajatii care s-au angajat in ultimele 4 luni ale anului, intre anii 1981 si 1983, 
-- nu primesc comision si lucreaza ca analisti . Se va afisa si data semnarii contractului de angajare, 
-- stiind ca aceasta a fost urmatoarea zi de luni dupa data angajarii. 
-- Se va afisa numele concatentat cu functia (ex. "FORD is ANALYST"), 
-- functia, salariul anual (concatenat cu sirul 'USD'), comisionul (daca e nul se va afisa 0), 
-- data semnarii contractului (in format cu luna si anul complet, ex.'24-DECEMBER-1982') 
-- si se va ordona alfabetic dupa nume.
-- Antetul listei este nume_func, salariu_anual, comision, data_contract.
-- Se vor prezenta doua scripturi (metode de rezolvare) diferite.
-- Pentru testare, se va utiliza baza de date formata din tabelele EMP, DEPT si SALGRADE.


alter session set NLS_DATE_FORMAT='DD-MONTH-YYYY';
-- metoda 1
select
	concat(concat(e.ename, ' is '), e.job) Nume_ang,
	e.job Functie,
	concat(e.sal * 12, ' USD') "Salariu_anual",
	nvl(e.comm, 0) "Comision",
	e.hiredate "Data contract"
from
	emp e
where
	e.job = 'ANALYST' and
	(extract(year from e.hiredate) >= 1981 and extract(year from e.hiredate) <= 1983) and
	(extract(month from e.hiredate) = 12 or
		extract(month from e.hiredate) = 11 or
		extract(month from e.hiredate) = 10 or
		extract(month from e.hiredate) = 9)
order by e.ename;

-- metoda 2
select
	ename || ' is ' || job Nume_ang,
	job Functie,
	sal*12  || ' ' || 'USD' "Salariu_anual",
	nvl(comm, 0) "Comision",
	hiredate "Data contract"
from
	emp
where
	job like 'ANALYST' and
	(extract(year from hiredate) between 1981 and 1983) and
	(extract(month from hiredate) between 9 and 12)
order by ename;

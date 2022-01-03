-- select ename "nume_angajat", job "job", 
-- 	length(job) - length(replace(job, substr(ename, length(ename) - 1, 2), 'x')) AS "nr_aparitii"
-- 	from emp
-- 	where instr(job, substr(ename, length(ename) - 1, 2), 1, 1) > 0;

-- select ename "nume_angajat", job "job", REGEXP_COUNT(job, substr(ename, length(ename)-1,2)) 
-- AS "nr_aparitii"
-- from emp
-- where instr(job, substr(ename, length(ename) - 1, 2), 1, 1) > 0;

-- select
-- 	a1.nume,
-- 	d1.den_dep,
-- 	extract(MONTH from a1.data_ang) as luna_ang,
-- 	extract(YEAR from a1.data_ang) as an_ang,
-- 	a1.salariu * &1 * ABS( LOG(2,  ((sysdate - a1.data_ang) / 365) ) / ((POWER(((sysdate - a1.data_ang) / 365), 2) + 1) * SIN(POWER(((sysdate - a1.data_ang) / 365), 2) + 1) ) )  prima_ang,
-- 	a2.nume nume_sef,
-- 	d2.den_dep den_dep_sef,
-- 	extract(MONTH from a2.data_ang) as luna_sef,
-- 	extract(YEAR from a2.data_ang) as an_sef
-- from 
-- 	angajati a1,
-- 	angajati a2,
-- 	departamente d1,
-- 	departamente d2
-- where
-- 	a1.id_dep = d1.id_dep and
-- 	a2.id_dep = d2.id_dep and
-- 	a1.id_sef = a2.id_ang and
-- 	length(a1.nume) <= 5 and
-- 	extract(YEAR from a1.data_ang) = extract(YEAR from a2.data_ang)
-- order by 1;

-- select 
-- 	concat(concat('*', ename), '*') nume,
-- 	extract(year from sysdate) - extract(year from hiredate) vechime,
-- 	lpad(sal, 10, '$') salariu,
-- 	power(5, sqrt((sysdate - hiredate)/365)) prima,
-- 	(sysdate - hiredate)/365 ceva
-- from emp
-- where ename like '%L%'
-- order by prima;

-- select
-- 	concat(concat('*', ename), '*') nume,
-- 	round(months_between(sysdate, hiredate) / 12) vechime,
-- 	lpad(sal, 10, '$') salariu,
-- 	power(5, sqrt(months_between(sysdate, hiredate) / 12)) prima,
-- 	months_between(sysdate, hiredate) / 12 ceva
-- from emp
-- where (length(ename) > length(replace(ename,'L','')))
-- order by 4;


-- -- metoda 1
-- select 
-- 	concat(concat('*', ename), '*') nume,
-- 	extract(year from sysdate) - extract(year from hiredate) vechime,
-- 	lpad(sal, 10, '$') salariu,
-- 	power(5, sqrt((sysdate - hiredate)/365)) prima
-- from emp
-- where ename like '%L%'
-- order by prima;

-- -- metoda 2
-- select 
-- 	'*'||ename||'*' nume,
-- 	round(months_between(sysdate, hiredate) / 12) vechime,
-- 	lpad(sal, 10, '$') salariu,
-- 	power(5, sqrt(months_between(sysdate, hiredate) / 12)) prima
-- from emp
-- where (length(ename) > length(replace(ename,'L','')))
-- order by 4;

-- metoda 1
select 
	concat(concat('*', ename), '*') nume,
	extract(year from sysdate) - extract(year from hiredate) vechime,
	lpad(sal, 10, '$') salariu,
	power(5, sqrt((sysdate - hiredate)/365)) prima
from emp
where ename like '%L%'
order by prima;

-- metoda 2
select 
	'*'||ename||'*' nume,
	round(months_between(sysdate, hiredate) / 12) vechime,
	lpad(sal, 10, '$') salariu,
	power(5, sqrt(months_between(sysdate, hiredate) / 12)) prima
from emp
where (length(ename) > length(replace(ename,'L','')))
order by 4;

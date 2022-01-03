-- select to_char (sysdate, 'DD-MM-YYYY') data_curenta 
-- from dual;

-- select to_date(15112006, 'DD-MM-YYYY') data_ex
-- from dual;

-- select to_char(-10000, '$999999.99MI') valoare
-- from dual;

-- select to_number('$10000.00-', '$999999.99MI') valoare
-- from dual;

-- Ex 1.

-- select nume, to_char (data_ang, 'dd-mm-yyyy') data_ang
-- from angajati
-- where to_char (data_ang, 'YYYY') like '1982';

-- select nume, to_char (data_ang, 'dd-mm-yyyy') data_ang
-- from angajati
-- where to_date(to_char(data_ang, 'YYYY'), 'YYYY') = 
-- 	  to_date(to_char(1982), 'YYYY');

-- select nume, to_char (data_ang, 'dd-mm-yyyy') data_ang
-- from angajati
-- where to_number(to_char(data_ang, 'YYYY')) = 1982;


-- Ex 2.
-- column numar format 99999
-- select 123.14 numar from dual;

-- column numar format 999.99
-- select 123.14 numar from dual;


-- column numar format $999.99
-- select 123.14 numar from dual;

-- column numar format 00999.99
-- select 123.14 numar from dual;
-- select 0.14 numar from dual;

-- column numar format 9990.99
-- select 123.14 numar from dual;
-- select 0.14 numar from dual;

-- DECODE
-- select nume, functie, salariu,
-- 	decode(functie, 'MANAGER', salariu * 1.25,
-- 					'ANALYST', salariu * 1.24,
-- 					salariu/4) prima
-- from angajati
-- where id_dep = 20
-- order by functie;


-- Ex 3.
-- select nume, functie, salariu,
-- 	to_char (data_ang, 'YYYY') an_ang,
-- 	decode(sign(data_ang - to_date('1-JAN-1982')),
-- 		-1, salariu * 1.25,
-- 		salariu * 1.1) prima
-- from angajati
-- where id_dep = 20
-- order by functie;

-- select case lower(locatie)
-- 	when 'new york' then 1
-- 	when 'dallas' then 2
-- 	when 'chicago' then 3
-- 	when 'boston' then 4
-- 	end cod_dep
-- from departamente;

-- select avg(salariu) salariu from angajati;
-- select avg(all salariu) salariu from angajati;
-- select avg(distinct salariu) salariu from angajati;

-- select id_dep, avg(salariu) from angajati
-- group by id_dep
-- order by 1;

-- select id_dep, count(*) nr_ang,
-- 	count(salariu) count,	
-- 	count(all salariu) count_all,
-- 	count(distinct salariu) count_distinct
-- from angajati
-- group by id_dep
-- order by 1;

-- select id_dep,
-- 	count (functie) count,
-- 	count(distinct functie) count_distinct
-- from angajati
-- group by id_dep
-- having count (distinct functie) >= 2
-- order by 1;

-- select d.den_dep,
-- 	min(a.salariu) sal_min,
-- 	min(distinct a.salariu) sal_min_d,
-- 	max(a.salariu) sal_max,
-- 	max(distinct a.salariu) sal_max_d,
-- 	sum(a.salariu) sal_sum,
-- 	sum(distinct a.salariu) sal_sum_d
-- from angajati a natural join departamente d
-- group by d.den_dep
-- order by d.den_dep;

-- select id_dep,
-- 	variance(salariu) sal_varstd,
-- 	variance(distinct salariu) sal_varstd_d,
-- 	stddev(salariu) sal_devstd,
-- 	stddev(distinct salariu) sal_devstd_d,
-- 	stddev(comision) com_devstd
-- from angajati
-- group by id_dep
-- order by 1;

select * from emp;

-- rezolvare test lab7
select
	e.job functie,
	case count(b.job)
		when 0 then 'NU'
		else 'DA'
	end exista_sef,
	count(e.job) nr_ang,
	count(distinct g.grade) nr_grile_sal_d,
	min(e.sal) sal_min,
	round(avg(e.sal), 2) sal_mediu,
	max(e.sal) sal_max
from
	emp e
	join emp b
		on e.mgr = b.empno(+)
	join salgrade g
		on e.sal between g.losal and g.hisal
group by
	e.job;


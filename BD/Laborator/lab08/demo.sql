-- -- select * 
-- -- from
-- -- (
-- -- 	select ename, sal
-- -- 	from emp
-- -- 	order by sal
-- -- )
-- -- where rownum <= 3;


-- -- select ename, sal
-- -- from emp
-- -- order by sal
-- -- fetch next 3 rows only;

-- -- Ex 1
-- select id_dep, nume, functie, salariu
-- from angajati
-- where salariu = (select max(salariu)
-- 					from angajati);

-- -- Ex 2
-- select id_dep, nume, functie, salariu
-- from angajati
-- where 
-- 	not id_dep = 20 and
-- 	functie in (select functie
-- 					from angajati where id_dep = 20)
-- order by functie;

-- -- Ex 3
-- select nume, functie, data_ang
-- from angajati
-- where data_ang not in
-- (
-- 	select distinct (data_ang)
-- 		from angajati
-- 		where to_char(data_ang, 'MON')
-- 		in ('DEC', 'JAN', 'FEB')
-- )
-- order by nume;

-- -- Ex 4
-- select id_dep, den_dep, nume, salariu
-- from angajati
-- 	natural join departamente
-- where salariu in
-- (
-- 	select max(salariu)
-- 	from angajati
-- 	group by id_dep
-- )
-- order by den_dep;

-- -- Ex 5
-- select id_dep, nume, functie, data_ang
-- from angajati
-- where
-- 	(to_char(data_ang, 'YYYY'), functie) in
-- 	(
-- 		select to_char(data_ang, 'YYYY'), functie
-- 		from angajati
-- 		where lower(nume) = 'jones'
-- 	);

-- -- Ex 6
-- select id_dep, nume, salariu
-- from angajati
-- where (id_dep, salariu + nvl(comision, 0)) in
-- 		(select id_dep, min(salariu + nvl(comision, 0))
-- 			from angajati
-- 			group by id_dep)
-- order by id_dep;

-- -- Ex 7
-- select nume, functie, data_ang, salariu
-- from angajati
-- where salariu >
-- 	(select max(salariu)
-- 		from angajati
-- 		where id_dep = 
-- 				(select id_dep
-- 					from departamente
-- 					where lower(den_dep) = 'sales'));



-- -- Ex 8
-- select 
-- 	a.id_dep,
-- 	a.nume,
-- 	a.functie,
-- 	a.salariu
-- from
-- 	angajati a
-- where
-- 	a.salariu > (select avg(b.salariu)
-- 					from angajati b
-- 					where b.id_dep = a.id_dep)
-- order by a.id_dep;

-- -- Ex 9


-- -- Ex 10
-- select
-- 	b.id_dep,
-- 	a.den_dep,
-- 	b.max_sal_dep
-- from
-- 	departamente a,
-- 	(select id_dep, max(salariu) max_sal_dep
-- 		from angajati
-- 		group by id_dep) b
-- where a.id_dep = b.id_dep
-- order by b.id_dep;

select
    e1.ename nume,
    e1.sal salariu,
    d1.loc locatie,
    e2.ename sef,
    e2.sal salariu_sef
from
    emp e1 natural join dept d1
   	inner join emp e2
   	on e1.mgr = e2.empno
where
    months_between(e2.hiredate, e1.hiredate) >= 4 and
    d1.loc not in (select loc 
    				from dept 
    				where loc = 'DALLAS' or loc = 'CHICAGO');


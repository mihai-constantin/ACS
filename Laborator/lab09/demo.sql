-- select * from emp;


-- select distinct(data_ang)
-- from angajati
-- where to_char(data_ang, 'MON') IN ('DEC', 'JAN', 'FEB');

-- ex 1
-- select	d.den_dep,
-- 		a.functie,
-- 		count(a.id_ang) nr_ang
-- from angajati a
-- 	natural join departamente d
-- group by	d.den_dep,
-- 			a.functie
-- having count(a.id_ang) = (select max(count(id_ang))
-- 							from angajati
-- 							group by id_dep,
-- 									 functie);

-- ex 2
-- define id_dep = 30
-- select	d.den_dep,
-- 		a.nume,
-- 		a.functie,
-- 		a.comision
-- from 	
-- 	angajati a
-- 	inner join departamente d
-- 	on a.id_dep = d.id_dep
-- group by
-- 	d.den_dep,
-- 	a.nume,
-- 	a.functie,
-- 	a.comision
-- having max(a.comision) in (select max(comision)
-- 							from angajati
-- 							where id_dep = &id_dep
-- 							group by id_dep)
-- order by 2;



-- ex 3
-- select 
-- 	a.nume,
-- 	a.functie,
-- 	a.data_ang,
-- 	a.salariu
-- from
-- 	angajati a,
-- 	(select id_dep,
-- 			max(salariu) sal_max_dep
-- 		from angajati
-- 		group by id_dep) b
-- group by
-- 	a.nume,
-- 	a.functie,
-- 	a.data_ang,
-- 	a.salariu
-- having a.salariu = max(b.sal_max_dep)
-- order by a.nume;



-- ex 4
-- select nume nume_ang,
-- 		(select nume
-- 			from angajati
-- 			where id_ang = a.id_sef) nume_sef
-- from angajati a
-- where id_dep = 20
-- order by nume;


-- ex 5
-- select id_dep, nume, functie
-- from angajati a
-- where id_dep in (10, 20)
-- order by (select count(*)
-- 			from angajati b
-- 			where a.id_dep = b.id_dep) desc;


-- ex 6
select 	id_dep,
		nume,
		functie,
		salariu
from angajati
where salariu > some(select distinct(salariu)
		from angajati
		where functie = 'SALESMAN')
order by id_dep, nume;

-- ex 7

-- Să se creeze tabela Statistica_Sefi, cu următoarele coloane:
-- - Nume_Sef
-- - Venit_Sef
-- - ​Grila_Salariala_Subalterni​ 
-- (grila salarială a subalternilor pentru care el este șef)
-- - Numar_Subalterni 
-- (numărul subalternilor pentru acest șef cu această ​grilă​)
-- - Medie_Venit_Subalterni 
-- (media veniturilor subalternilor cu acea grila salarială)
-- Să se populeze tabela în conformitate 
-- cu aceste cerințe pentru fiecare 
-- șef din companie, persoană din 
-- tabela EMP care are minim un subaltern, 
-- care este din același departament cu minim un subaltern.

drop table t1;
drop table t2;
drop table Statistica_Sefi;

create table t1
as
select
	ang.ename Nume_ang,
	ang.sal Sal_ang,
	grila.grade Grila_ang,
	sef.ename Nume_sef
from
	emp ang,
	emp sef,
	salgrade grila
where
	ang.mgr = sef.empno and
	ang.sal >= grila.losal and ang.sal <= grila.hisal
order by 2;

select * from t1;

create table t2
as
select
	ang.Nume_sef Nume_Sef,
	count(ang.Nume_ang) Numar_Subalterni,
	avg(ang.Sal_ang) Medie_Sal_ang,
	ang.Grila_ang Grila_subalterni
from
	t1 ang
group by
	ang.Nume_sef,
	ang.Grila_ang;

select * from t2;


create table Statistica_Sefi
as 
select
	sef.Nume_Sef Nume_Sef,
	ang.sal Venit_Sef,
	sef.Grila_subalterni Grila_subalterni,
	sef.Numar_Subalterni Numar_Subalterni,
	sef.Medie_Sal_ang Medie_Venit_Subalterni
from
	t2 sef,
	emp ang
where
	ang.ename = sef.Nume_Sef;

select * from Statistica_Sefi;

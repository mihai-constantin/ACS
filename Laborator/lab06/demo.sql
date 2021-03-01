select concat(concat(nume, ' este '), functie) ANG_FUNC
	from angajati
	where id_ang = 7839;

select initcap(nume) ex_initcap
	from angajati
	where id_ang = 7839;

select replace('JACK si JUE', 'J', 'BL') EX_REPLACE
	from dual;

select rpad(nume, 10, '*') EX_RPAD
	from angajati
	where id_dep = 10;

select lpad(nume, 10, '*') EX_LPAD
	from angajati
	where id_dep = 10;

select rtrim('Popescu', 'scu') from dual;

select substr('Popescu', 2, 3) from dual;

select instr('Protopopescu', 'op', 3, 2) from dual;

select translate('Oana are mere', 'Om', ' p') from dual;

-- functii pentru date calendaristice
select nume, data_ang, ADD_MONTHS(data_ang, 3) data_mod
	from angajati
	where id_dep = 10;

select nume, data_ang, LAST_DAY(data_ang) ultima_zi
	from angajati
	where id_dep = 10;

select NEXT_DAY('31-MAR-2014', 'MONDAY') urmatoarea_luni
	from dual;

select nume, data_ang,
	MONTHS_BETWEEN('09-JUN-1982', data_ang) luni_vechime1,
	MONTHS_BETWEEN(data_ang, '09-JUN-1982') luni_vechime2
from angajati
where id_dep = 10;

select
	data_ang,
	round(data_ang, 'YEAR') rot_an
from angajati
where id_ang = 7369;

select
	data_ang,
	round(data_ang, 'MONTH') rot_luna
from angajati
where id_ang = 7369;

select
	data_ang,
	trunc(data_ang, 'YEAR') trun_an
from angajati
where id_ang = 7369;

select
	data_ang,
	trunc(data_ang, 'MONTH') trun_luna
from angajati
where id_ang = 7369;

select sysdate from dual;

select extract(day from sysdate) from dual;
select extract(month from sysdate) from dual;
select extract(year from sysdate) from dual;

-- schimbare data format



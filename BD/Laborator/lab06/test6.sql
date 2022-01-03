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

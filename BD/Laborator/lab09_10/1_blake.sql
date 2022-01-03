-- Sa se creeze o tabela denumita ANG_BLAKE care sa contina toti 
-- angajatii veniti in firma in alt an decat seful cu cei mai multi subordonati. 
-- Structura tabelei este urmatoarea: 
-- Nume_angajat, 
-- Den_departament, 
-- An_angajare, 
-- Ani_vechime
-- Vechimea se va calcula ca si numar natural.
-- Pentru testare, se va utiliza baza de date 
-- formata din tabelele EMP, DEPT si SALGRADE.

create table table1 as 
select  
    sef.ename Nume_Sef, 
    sef.hiredate Data_angajare_sef, 
    (select count(*) from emp ang where ang.mgr = sef.empno) Numar_Subalterni 
from  
    emp sef;

select 
    ang.ename Nume_angajat, 
    dep.dname Denumire_departament, 
    extract(year from ang.hiredate) An_angajare, 
    extract(year from sysdate) - extract(year from ang.hiredate) Ani_vehime 
from  
    emp ang, 
    dept dep 
where 
    ang.deptno = dep.deptno and 
    extract(year from ang.hiredate) != (select 
            extract(year from subordonati.Data_angajare_sef) an_ang 
            from 
                table1 subordonati 
            where 
                subordonati.Numar_Subalterni = (select 
                                    max(Numar_Subalterni) 
                                    from  
                                        table1));
    
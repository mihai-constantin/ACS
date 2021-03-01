-- SELECT id_ang, nume, functie, (salariu + nvl(comision, 0)) * 12 salariu_anual, comision, id_dep
-- 	FROM angajati
-- 	WHERE id_dep = &id_dep AND (salariu + nvl(comision, 0)) * 12 > &venit_mediu_anual;

-- SELECT nume, functie, data_ang, id_dep, (salariu + nvl(comision, 0)) * 12 venit_anual
-- 	FROM angajati
-- 	WHERE id_dep = &&id_dep AND (salariu + nvl(comision, 0)) * 12 > &venit_mediu_anual;

-- SELECT id_ang, nume, functie, (salariu + nvl(comision, 0)) * 12 salariu_anual, comision, id_dep
-- 	FROM angajati
-- 	WHERE id_dep = &1 AND (salariu + nvl(comision, 0)) * 12 > &2;

-- accept nr_dep char prompt 'Introduceti nr_dep: '
-- accept venit_mediu_anual char prompt 'Introduceti venit_mediu_anual: '

-- SELECT id_ang, nume, functie, (salariu + nvl(comision, 0)) * 12 salariu_anual, comision, id_dep
-- 	FROM angajati
-- 	WHERE id_dep = &nr_dep AND (salariu + nvl(comision, 0)) * 12 > &venit_mediu_anual;

-- undefine nr_dep
-- undefine venit_mediu_anual


-- Metoda 1
-- SELECT id_dep, &salariu_maxim, id_ang, nume, salariu
-- 	FROM angajati
-- 	WHERE id_dep = &id_dep AND salariu > (&salariu_maxim / 2);

-- Metoda 2
-- SELECT id_dep, &&salariu_maxim, id_ang, nume, salariu
-- 	FROM angajati
-- 	WHERE id_dep = &id_dep AND salariu > (&salariu_maxim / 2);

-- Metoda 3
-- SELECT id_dep, &2, id_ang, nume, salariu
-- 	FROM angajati
-- 	WHERE id_dep = &1 AND salariu > (&2 / 2);

-- Metoda 4

accept salariu_maxim char prompt 'Introduceti salariu_maxim: '
accept id_dep char prompt 'Introduceti id_dep: '

SELECT id_dep, &salariu_maxim, id_ang, nume, salariu
	FROM angajati
	WHERE id_dep = &id_dep AND salariu > (&salariu_maxim / 2);
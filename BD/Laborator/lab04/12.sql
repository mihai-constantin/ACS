-- SELECT
-- 	id_ang AS ecuson,
-- 	nume,
-- 	functie,
-- 	salariu + nvl(comision, 0) AS "Venit lunar"
-- FROM angajati
-- WHERE id_ang IN (7499, 7902, 7876)
-- ORDER BY nume;

SELECT
	id_ang AS ecuson,
	nume,
	functie,
	salariu + nvl(comision, 0) AS "Venit lunar"
FROM angajati
WHERE id_ang = 7499 OR id_ang = 7902 OR id_ang = 7876
ORDER BY nume;
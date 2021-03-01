-- SELECT
-- 	id_dep departament,
-- 	functie,
-- 	nume,
-- 	data_ang AS "Data angajarii"
-- FROM angajati
-- WHERE data_ang BETWEEN '1-MAY-1981' AND '31-DEC-1981'
-- ORDER BY 1, 2 DESC;


SELECT
	id_dep departament,
	functie,
	nume,
	data_ang AS "Data angajarii"
FROM angajati
WHERE data_ang >= '1-MAY-1981' AND data_ang <= '31-DEC-1981'
ORDER BY 1, 2 DESC;
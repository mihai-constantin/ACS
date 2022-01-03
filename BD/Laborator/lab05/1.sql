-- metoda 1
-- SELECT nume, functie, den_dep
-- FROM angajati, departamente
-- WHERE functie = 'ANALYST';

-- metoda 2

SELECT nume, functie, den_dep
FROM angajati
	CROSS JOIN departamente
WHERE functie = 'ANALYST';
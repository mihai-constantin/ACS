-- Functia are 7 caractere + numele incepe cu litera F

SELECT 
	id_ang AS ecuson,
	nume,
	functie,
	data_ang AS "Data Angajarii"
FROM angajati
WHERE nume LIKE 'F%' AND FUNCTIE LIKE '_______'; 
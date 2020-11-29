# Tema 2 SPRC 2020 - 2021

## Implementare rute

### Country

* **POST** (Adaugare tara in baza de date): localhost:3000/api/countries
  * 201 Created - se adauga o tara noua in tabela countries
  * 400 Bad Request - daca cererea nu contine toate field-urile necesare
  * 409 Conflict - daca se incearca adaugarea unei tari care este deja in baza de date (numele tarii trebuie sa fie unic)
  * 500 Internal Server Error - eroare cauzata de mongoDB

* **GET** (Afisarea tuturor tarilor din baza de date): localhost:3000/api/countries
  * 200 OK - se afiseaza toate tarile din baza de date
  * 500 Internal Server Error - eroare cauzata de mongoDB

* **GET BY ID** (Afisarea tarii corespunzatoare id-ului din cerere): localhost:3000/api/countries/:countryId
  * 200 OK - se afiseaza tara cu id-ul countryId
  * 404 Not Found - situatie in care id-ul are un format invalid sau tara nu exista in baza de date; se afiseaza un mesaj corespunzator

*  **PUT** (Update informatii tara): localhost:3000/api/countries/:countryId
  * 200 OK - se updateaza field-urile corespunzatoare
  * 400 Bad Request - lipsesc unele field-uri din request
  * 404 Not Found - id-ul din request este invalid sau nu are niciun corespondent in baza de date
  * 409 Conflict - cand se doreste update la numele tarii, dar tara respectiva deja exista in baza de date

* **DELETE** (Stergerea unei tari): localhost:3000/api/countries/:countryId
  * 200 OK - se sterge tara respectiva din baza de date, impreuna cu orasele si temperaturile corespunzatoare acestora
  * 404 Not Found - id-ul din request este invalid sau nu are niciun corespondent in baza de date
  * 500 Internal Server Error - eroare cauzata de mongoDB

### City

* **POST** (Adaugare oras in baza de date): localhost:3000/api/cities
  * 201 Created - adaugare oras
  * 400 Bad Request - lipsesc unele field-uri din request
  * 404 Not Found - daca country_id-ul este invalid sau nu are corespondent in baza de date
  * 409 Conflict - daca se doreste adaugarea unui oras intr-o tara in care este deja existent orasul respectiv

* **GET** (Afisarea tuturor oraselor): localhost:3000/api/cities
  * 200 OK - afisarea tuturor oraselor din baza de date
  * 500 Internal Server Error - eroare cauzata de mongoDB

* **GET BY ID** (Afisarea orasului corespunzator id-ului din cerere): localhost:3000/api/cities/:cityId
  * 200 OK - afisare oras 
  * 404 Not Found - situatie in care id-ul are un format invalid sau orasul nu exista in baza de date; se afiseaza un mesaj corespunzator

* **GET BY COUNTRY** (Afisarea tuturor oraselor care apartin unei tari): localhost:3000/api/cities/country/:countryId
  * 200 OK - afisarea tuturor oraselor din tara respectiva
  * 404 Not Found - daca countryId este invalid sau nu exista in tabela countries

* **PUT** (Update informatii oras): localhost:3000/api/cities/:cityId
  * 200 OK - se updateaza informatiile corespunzatoare cererii
  * 400 Bad Request - lipsesc unele field-uri din request
  * 404 Not Found - daca country_id/city_id este invalid sau nu are corespondent in baza de date
  * 409 Conflict - in situatia in care se doreste update la numele tarii, dar in tara respectiva exista deja orasul in cauza

* **DELETE** (Stergerea unui oras): localhost:3000/api/cities/:cityId
  * 200 OK - se sterge intregistrarea orasului din tabelul corespunzator, precum si temperaturile asociate cu acesta
  * 404 Not Found - id-ul din request este invalid sau nu are niciun corespondent in baza de date
  * 500 Internal Server Error - eroare cauzata de mongoDB

### Temperatures

CONSTANTIN MIHAI | 321CD

TEMA 3 | PROTOCOALE DE COMUNICATII

------------------------------------
Client HTTP. Comunicatie cu REST API
------------------------------------

Am folosit ca schelet de pornire laboratorul 10 de HTTP. 
Acesta are urmatoarea structura: 

- client.c: clientul HTTP - apeleaza rutele expuse de catre server folosind
							metode de tip GET sau POST

- helpers.c: contine functii precum open_connection (se deschide conexiunea), 
			 close_connection (se inchide conexiunea cu serverul), 
			 send_to_server (se trimite la server mesajul), receive_from_server 
			 (se primeste raspuns de la server), compute_message (creeaza 
			 mesajul de request), error (afiseaza un mesaj de eroare)

- helpers.h: fisier header ce defineste functiile din helpers.c

- requests.c: contine cele doua metode de GET si POST efectuate de client
			  (compute_get_request si compute_post_request)

- requests.h: fisier header ce defineste functiile din requests.c

- Makefile: contine regulile de build, run si clean necesare pentru rularea,
			respectiv stergerea fisierului executabil client

De asemenea, am folosit functia get_ip din laboratorul 9 de DNS pentru a
determina adresa IP a unui domeniu (task 5).

----------------------------
IMPORTANT! EXEMPLU DE RULARE
----------------------------
Pentru rularea temei se va folosi fisierul Makefile. 
Se ruleaza comenzile: "make build" si "make run". Pe masura ce codul se executa
se vor afisa in consola mesajele trimise si primite in urma fiecarui task.

------
TASK 1
------
Am efectuat o simpla cerere de tip GET la URL-ul /task1/start.
Am printat mesajul trimis si primit.

------
TASK 2
------
Pentru a parsa JSON-ul primit in mesaj, am folosit biblioteca json-c.
Am extras campurile necesare precum enunt, url, method, type, am format un 
buffer login de forma "username=xxx&password=xxx" si am format cooki-urile
folosind o functie auxiliara getCookies().

------
TASK 3
------
Am format un buffer ce retine raspunsurile la ghicitorile primite, de forma:
"raspuns1=omul&raspuns2=numele", am extras id-ul si token-ul pentru a crea
buffer-ul pentru autentificare. Am extras de asemenea si cooki-urile, trimitand
intregul mesaj.

------
TASK 4
------
Am efectuat o simpla cerere de tip GET la URL-ul /task4/key (cheia extrasa).
Am trimis mesajul cu tot cu cookies si cu token-ul pentru autentificare.

------
TASK 5
------
In prima faza, am obtinut adresa IP pentru domeniul api.openweathermap.org,
folosind functia get_ip (const char*).
In continuare, am efectuat o cerere de tip GET pe url-ul din "data.url" la
adresa aflata mai sus, formand si url_params, trimis ca parametru functiei
compute_get_request. Pasul final a fost efectuarea unei cereri de tip POST
la "task5/treasure" (url extras) continand mesajul primit, precum si 
cooki-urile si token-ul pentru autentificare.

--------------------
DETALII IMPLEMENTARE
--------------------

Tema a fost realizata pe un sistem de operare macOS Mojave 10.14.4.


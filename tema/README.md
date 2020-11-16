# Tema 1 SPRC 2020-20221
## RPC + DB

### Cerinta
* Realizarea unei aplicatii client-server bazata pe RPC cu cereri/raspunsuri multiple prin care se poate gestiona o baza de date stocata la distanta

### Observatii
* Pentru a putea avea mai multi clienti rulati in acelasi timp, citirea se realizeaza de la stdin, nu dintr-un fisier.
* Fisierele de test se gasesc in directorul tests.
* **Avand in vedere ca citirea se realizeaza de la stdin, tocmai pentru a simula prezenta mai multor clienti in acelasi timp, continutul fisierelor de test trebuie simulate de mana.**

### Rulare
* se executa comanda make -f Makefile.tema
* serverul se ruleaza cu ./tema_server
* un client se ruleaza cu ./tema_client localhost
    * in acest moment, se pot introduce de la tastatura in client comenzi pentru prelucrare

### Implementare
* Clientul dispune de mai multe comenzi pe care le poate folosi, asteptand un raspund de la server in urma acestora.
* Comezile puse la dispozitie sunt:
    * **login <nume_client>**: clientul se autentifica la server
        * serverul intoarce un id unic daca autentificarea s-a realizat cu succes, sau un cod de eroare daca clientul este deja autentificat
        * in client se va afisa un mesaj corespunzator daca actiunea a avut loc cu succes sau nu
    * **logout**: clientul se delogheaza
        * serverul va intoarce id-ul clientului care s-a delogat
        * daca clientul doreste sa se delogheze, dar nu este autentificat in sistem, se va generea un mesaj de eroare
        * in urma delogarii clientului, serveru-ul va sterge perechea (user, session_key) din lista de clienti autentificati, precum si memoria utilizatorului din baza de date
    * **load**: clientul initializeaza baza de date proprie cu datele din fisierul corespunzator (client_name.rpcdb)
        * daca fisierul nu exista, se va crea unul
        * daca fisierul exista, se vor introduce in baza de date valorile din fisierul corespunzator
        * comanda load are loc doar daca clientul este autentificat in sistem; altfel, acesta va primi o eroare corespunzatoare
    * **add <data_id> <no_values> <value1> <value2> ... <value_no_values>**: adauga o inregistrare in baza de date a clientului autentificat
        * daca operatia add se realizeaza in momentul in care user-ul nu este autentificat in sistem sau inainte de comanda load, se genereaza un mesaj de eroare corespunzator
        * in caz de succes, serverul va insera in baza de date noua inregistrare
        * in cazul in care inregistrarea deja exista (avem deja o intregistrare in baza de date cu un data_id egal cu cel pe care vrem sa-l adaugam), se va face update la inregistrare
    * **update <data_id> <no_values> <value1> <value2> ... <value_no_values>**: updateaza o intregistrare in baza de date a clientului autentificat
        * daca operatia update se realizeaza in momentul in care user-ul nu este autentificat in sistem sau inainte de comanda load, se genereaza un mesaj de eroare corespunzator
        * in caz de succes, serverul va updata inregistrarea din baza de date
        * in cazul in care inregistrarea nu exista, intregistrarea se va insera in baza de date
    * **read <data_id>**: se citeste o intregistrare din baza de date
        * daca operatia read se realizeaza in momentul in care user-ul nu este autentificat in sistem sau inainte de comanda load, se genereaza un mesaj de eroare corespunzator
        * in caz de succes, serverul intoarce intregistrarea gasita
        * daca intregistrarea cautata nu exista in baza de date a user-ului autentificat, se va genera un mesaj de eroare
    * **del <data_id>**: se sterge o intregistrare din baza de date
        * daca operatia del se realizeaza in momentul in care user-ul nu este autentificat in sistem sau inainte de comanda load, se genereaza un mesaj de eroare corespunzator
        * daca intregistrarea cautata nu exista in baza de date a user-ului autentificat, se va genera un mesaj de eroare
        * in caz de succes, se sterge inregistrarea din baza de date a utilizatorului autentificat
    * **store**: se memoreaza baza de date al utilizatorului autentificat intr-un fisier text cu numele client_name.rpcdb
        * daca operatia store se realizeaza in momentul in care user-ul nu este autentificat in sistem sau inainte de comanda load, se genereaza un mesaj de eroare corespunzator
        * in caz de succes, se suprascrie fisierul corespunzator cu datele aflate in momentul curent in baza de date a clientului
    * **get_stat <data_id>**: ofera statistici cu privire la o inregistrare din baza de date a utilizatorului curent
        * * daca operatia get_stat se realizeaza in momentul in care user-ul nu este autentificat in sistem sau inainte de comanda load, se genereaza un mesaj de eroare corespunzator
    * **get_stat_all**: ofera statistici cu privire la toate inregistrarile din baza de date a utilizatorului curent
        * * daca operatia get_stat_all se realizeaza in momentul in care user-ul nu este autentificat in sistem sau inainte de comanda load, se genereaza un mesaj de eroare corespunzator

### Concluzii


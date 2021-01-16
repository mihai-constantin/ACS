# Tema 3 SPRC 2020-2021

## Rulare
* din directorul tema3-sprc se ruleaza scriptul run.sh care va crea urmatoarele servicii:
  * **registry** pentru *Docker Swarm*
  * **sprc3_adaptor**: componenta care primeste mesaje de la senzori (in cazul de fata de la un client) si trimite meesajele catre broker-ul de MQTT
  * **sprc3_grafana**: componenta vizuala a aplicatiei in care apar datele prelucrate din baza de date
  * **sprc3_influxdb**: baza de date
  * **sprc3_mosquitto**: broker-ul de MQTT
* se acceseaza localhost:80/ pentru a vizualiza interfata grafica de grafana
  * username: asistent
  * parola: grafanaSPRC2020
* in acest moment nu avem nicio data in influxdb
* din directorul tema3-sprc se ruleaza ./client.sh pentru a simula un senzor de date
  * acesta se va conecta la portul 1883 (portul expus de serviciul sprc3_mosquitto (broker-ul MQTT)) pe localhost
  * clientul va trimite mesaje catre broker, iar acesta la randul sau, le va pasa catre adaptor
  * adaptorul prelucreaza datele primile, le memoreaza in baza de date, iar rezultatele sunt vizibile in interfata de grafana
* script-ul de client ruleaza intr-o bucla infinita; pentru oprire se executa combinatia de taste CTR+C
* se ruleaza script-ul clean.sh pentru a sterge serviciile si a parasi environment-ul de swarm
  * se poate rula ./clean.sh --volumes pentru a sterge si volumele asociate serviciilor de influxdb, respectiv grafana

## **IMPORTANT - Integrarea serviciului de client in stack-ul de swarm**
* daca se doreste integrarea serviciului de client in stack-ul de swarm, sunt necesare urmatoarele operatii
  * decomentarea liniilor comentate din fisierul stack.yml
  * decomentarea liniilor 12, respectiv 17 din script-ul run.sh (build-ul de client, respectiv adaugarea imaginii in registry)
  * linia 73 din client/client.py sa devina
    ```python
    data['timestamp'] = datetime.now() if 7 in indices else generate_date()
    ```
  * aceasta modificare din client.py e necesara pentru a vedea datele in grafana (daca lasam cu - timedelta(hours = 2) inseram datele in viitor; ori e o problema la timezone la grafana, ori trebuie setat timezone-ul in swarm - nu mi-am dat seama)
* se ruleaza script-ul ./run.sh
* se acceseaza localhost:80/ pentru grafana cu credentialele de mai sus

## Implementare
* Tema este structurata in urmatoarele sectiuni, detaliate mai jos.

### Adaptorul
* implementat in python folosind paho.mqtt
* se conecteaza la broker-ul de MQTT si se aboneaza la orice topic
* fiecare data pe care o primeste de la broker (datele pe care broker-ul le paseaza de la senzori (client in cazul nostru)) o memoreaza in baza de date
* daca variabila de environment DEBUG_DATA_FLOW este setata la *true* la comanda `docker service logs sprc3_adaptor` se vor afisa mesajele pe care adaptor-ul le-a procesat pana in momentul respectiv; altfel, nu se afiseaza niciun log

### Clientul
* implementat in python folosind paho.mqtt
* se conecteaza la portul 1883 al broker-ului de MQTT de pe localhost
* publica mesajele create
* mesajele sunt create random sunt forma unor string-uri de JSON-uri, utilizand urmatoarele liste
  ```python
  locations = ['UPB', 'UMFCD']
  stations = ['RPi_1', 'RPi_2', 'RPi_3']
  metrics = ['BAT', 'HUMID', 'TMP', 'AQI', 'RSSI', 'Alarm', 'status', 'timestamp']
  ```
  
### Grafana
* s-a folosit imaginea [grafana/grafana](https://hub.docker.com/r/grafana/grafana) pentru a crea serviciul
* portul expus pe localhost este 80
* atat sursa de date (influxdb), cat si dashboard-urile sunt create automat la rularea script-ului run.sh

### InfluxDB
* s-a folosit imaginea [influxdb](https://hub.docker.com/_/influxdb) pentru a crea serviciul
* niciun port nu este expus pe localhost
* baza de date folosita este *db1*

### Broker-ul MQTT
* s-a folosit imaginea [eclipse-mosquitto](https://hub.docker.com/_/eclipse-mosquitto) pentru a crea serviciul
* portul expus pe localhost este 1883, folosit de client pentru a publica mesajele

## Observatii
* setarea timpului in grafana este pentru ultimele 6 ore
  * pentru a se vedea rezultatele cat de cat, trebuie modificat time limit-ul la 5 sau 15 minute
* toata aplicatia expune doua porturi
  * 80, pentru vizualizarea datelor in grafana
  * 1883, pentru conectarea la broker-ul de MQTT
* serviciile din swarm sunt grupate in retele pentru o comunicare eficienta, asa cum s-a specificat in enuntul temei
* inserarea datelor in grafana este in functie de datele pe care le-am oferit in fisierul client.py
* in urma rularii clientului timp de 6 ore s-au obtinut graficele din directorul graphics

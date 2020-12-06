# Varianta single producer multiple consumers implementata cu MPI

## Rulare - pe fep
* Se executa comanda **make**, dupa care **make run**. Rezultatul se va gasi in fisierul *run.sh.o###*. 
* Avand in vedere ca rulam pe fep, vom avea un producator si 3 consumatori. In scriptul *run.sh*, numarul total de thread-uri este setat la 4.

## Producer
* Producatorul va insera in coada element cu element. Daca coada este plina, se va astepta pana cand consumatorul va extrage un element pentru a se putea insera din nou.

## Consumers
* Fiecare consumator va extrage un element din coada. El va calcula radical din elementul respectiv si va notifica producatorul ca exista un slot liber in coada.

# Varianta single producer multiple consumers implementata cu pthreads POSIX

## Rulare - pe fep
* Se executa comanda **make**, dupa care **make run**. Rezultatul se va gasi in fisierul *data.out*.

## Producer
* Producatorul va insera in coada element cu element. Daca coada este plina, se va astepta pana cand consumatorul va extrage un element pentru a se putea insera din nou.

## Consumers
* Fiecare consumator va extrage un element din coada. El va calcula radical din elementul respectiv si va notifica producatorul ca exista un slot liber in coada.

## Timpi
* 2^20: 4.270916s
* 2^21: 8.441302s

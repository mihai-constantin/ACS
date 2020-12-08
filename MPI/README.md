# Varianta single producer multiple consumers implementata cu MPI

## Rulare - pe fep
* Se executa comanda **make**, dupa care **make run ARGS=<dim>**. Rezultatul se va gasi in fisierul *run.sh.o###*. 
* Avand in vedere ca rulam pe fep, vom avea un producator si 3 consumatori. In scriptul *run.sh*, numarul total de thread-uri este setat la 4.

## Producer
* Producatorul va insera in coada element cu element. Daca coada este plina, se va astepta pana cand consumatorul va extrage un element pentru a se putea insera din nou.

## Consumers
* Fiecare consumator va extrage un element din coada. El va calcula radical din elementul respectiv si va notifica producatorul ca exista un slot liber in coada.

## Timpi
* In urma rularii de un numar semnificativ de ori, s-au obtinut rezultatele de mai jos pentru urmatoarele dimensiuni ale vectorului:
    * 2^20: 0.49367s
    * 2^21: 0.87576s
    * 2^22: 1.67272s
    * 2^23: 3.43341s
    * 2^24: 6.50322s
    * 2^25: 12.51834s
    
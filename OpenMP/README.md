# Varianta single producer multiple consumers implementata cu OpenMP

## Rulare - pe fep
* Se executa comanda **make**, dupa care **make run ARGS=<dim>**. Rezultatul se va gasi in fisierul *data.out*.

## Producer
* Producatorul va insera in coada element cu element. Daca coada este plina, se va astepta pana cand consumatorul va extrage un element pentru a se putea insera din nou.

## Consumers
* Fiecare consumator va extrage un element din coada. El va calcula radical din elementul respectiv si va notifica producatorul ca exista un slot liber in coada.

## Timpi
* In urma rularii de un numar semnificativ de ori, s-au obtinut rezultatele de mai jos pentru urmatoarele dimensiuni ale vectorului:
    * 2^20: 0.36022s
    * 2^21: 0.71265s
    * 2^22: 1.38178s
    * 2^23: 3.08811s
    * 2^24: 6.23075s
    * 2^25: 11.20191s
    
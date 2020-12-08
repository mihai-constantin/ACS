# Varianta single producer multiple consumers implementata cu pthreads POSIX

## Rulare - pe fep
* Se executa comanda **make**, dupa care **make run ARGS=<dim>**. Rezultatul se va gasi in fisierul *data.out*.

## Producer
* Producatorul va insera in coada element cu element. Daca coada este plina, se va astepta pana cand consumatorul va extrage un element pentru a se putea insera din nou.

## Consumers
* Fiecare consumator va extrage un element din coada. El va calcula radical din elementul respectiv si va notifica producatorul ca exista un slot liber in coada.

## Timpi
* S-a folosit scriptul *profiling.sh* pentru a rula programul de mai multe ori si a calcula o medie a timpilor obtinuti.
    * **rulare**: ./profile.sh *dim*, unde *dim* este exponentul lui 2 pentru dimensiunea datelor de intrare
* In urma rularii de un numar semnificativ de ori, s-au obtinut rezultatele de mai jos pentru urmatoarele dimensiuni ale vectorului:
    * 2^20: 4.54700s
    * 2^21: 8.49388s
    * 2^22: 16.38324s
    * 2^23: 29.05137s
    * 2^24: 60.91497s
    * 2^25: 113.08258s
    
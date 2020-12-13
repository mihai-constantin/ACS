# Varianta single producer multiple consumers implementata cu pthreads POSIX

## Sistem
* Programul a fost rulat pe fep.
* Avem asadar, un producator si 3 consumatori la fiecare executie.

## Rulare
* Se executa comanda **make**, dupa care **make run ARGS=<dim>**, unde dim este dimensiunea datelor de intrare.
* Rezultatul se va gasi in fisierul *data.out*.

## Producer
* Producatorul va insera in coada element cu element. Daca coada este plina, se va astepta pana cand un consumator va extrage un element pentru a se putea insera din nou.

## Consumers
* Fiecare consumator va extrage un element din coada. El va calcula radical din elementul respectiv si va notifica producatorul ca exista un slot liber in coada. Rezultatul calculat de fiecare consumator este pus in vectorul roots pe pozitia corespunzatoare.

## Timpi
* S-a folosit scriptul *profiling.sh* pentru a rula programul de mai multe ori si a calcula o medie a timpilor obtinuti.
    * **rulare**: ./profiling.sh *dim*, unde *dim* este exponentul lui 2 pentru dimensiunea datelor de intrare
        * **exemplu**: *./profiling.sh 20* va rula scriptul pentru o dimensiune a datelor de intrare egala cu 2^20
* In urma rularii de un numar semnificativ de ori, s-au obtinut rezultatele de mai jos pentru urmatoarele dimensiuni ale vectorului:
    * 2^20: 6.83992s
    * 2^21: 13.70993s
    * 2^22: 25.70177s
    * 2^23: 54.54097s
    * 2^24: 109.20019s
    * 2^25: 227.28415s
    
# Varianta single producer multiple consumers implementata cu pthreads POSIX

## Sistem
* Programul a fost rulat pe un sistem cu 4 core-uri cu hyperthreading.
* Avem asadar, un producator si 7 consumatori la fiecare executie.

## Rulare
* Se executa comanda **make**, dupa care **make run ARGS=<dim>**. Rezultatul se va gasi in fisierul *data.out*.

## Producer
* Producatorul va insera in coada element cu element. Daca coada este plina, se va astepta pana cand un consumator va extrage un element pentru a se putea insera din nou.

## Consumers
* Fiecare consumator va extrage un element din coada. El va calcula radical din elementul respectiv si va notifica producatorul ca exista un slot liber in coada. Rezultatul calculat de fiecare consumator este pus in vectorul roots pe pozitia corespunzatoare.

## Timpi
* S-a folosit scriptul *profiling.sh* pentru a rula programul de mai multe ori si a calcula o medie a timpilor obtinuti.
    * **rulare**: ./profile.sh *dim*, unde *dim* este exponentul lui 2 pentru dimensiunea datelor de intrare
* In urma rularii de un numar semnificativ de ori, s-au obtinut rezultatele de mai jos pentru urmatoarele dimensiuni ale vectorului:
    * 2^20: 4.90645s
    * 2^21: 10.18319s
    * 2^22: 20.86707s
    * 2^23: 42.90423s
    * 2^24: 87.38690s
    * 2^25: 179.47664s
    
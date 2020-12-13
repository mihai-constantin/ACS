# Varianta single producer multiple consumers implementata cu MPI + pthreads

## Sistem
* Programul a fost rulat pe un sistem cu 4 core-uri cu hyperthreading.
    * procesor Intel i7-8665U CPU @ 1.90Ghz 2.11GHz
    * 32GB RAM
* Avem asadar, un producator si 7 consumatori la fiecare executie.

## Rulare
* Se executa comanda **make**, dupa care **make run ARGS="<dim> <num_threads_per_process>"**. Rezultatul se va gasi in fisierul *data.out*.

## Producer
* Producatorul va insera in coada element cu element. Daca coada este plina, se va astepta pana cand un consumator va extrage un element pentru a se putea insera din nou.

## Consumers
* Fiecare consumator va extrage un element din coada. El va calcula radical din elementul respectiv si va notifica producatorul ca exista un slot liber in coada. Rezultatul calculat de fiecare consumator este pus in vectorul roots pe pozitia corespunzatoare.

## Timpi
* S-a folosit scriptul *profiling.sh* pentru a rula programul de mai multe ori si a calcula o medie a timpilor obtinuti.
    * **rulare**: ./profiling.sh *dim*, unde *dim* este exponentul lui 2 pentru dimensiunea datelor de intrare
    * fiecare proces(nod) are 4 thread-uri
* In urma rularii de un numar semnificativ de ori, s-au obtinut rezultatele de mai jos pentru urmatoarele dimensiuni ale vectorului:
    * 2^20:
    * 2^21: 
    * 2^22: 
    * 2^23: 
    * 2^24: 
    * 2^25: 
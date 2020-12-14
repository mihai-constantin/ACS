# Proiect SM 2020-2021: Single Producer - Multiple Consumers

## Implementare
* Producer
    * Producatorul va insera in coada element cu element.
    * Daca coada este plina, se va astepta pana cand un consumator va extrage un element pentru a se putea insera din nou.
* Consumers
    * Fiecare consumator va extrage un element din coada. El va calcula radical din elementul respectiv si va notifica producatorul ca exista un slot liber in coada. 
    * Rezultatul calculat de fiecare consumator este pus in vectorul roots pe pozitia corespunzatoare.

## Sistem
* Programul a fost rulat pe un sistem cu 4 core-uri cu hyperthreading.
    * procesor Intel i7-8665U CPU @ 1.90Ghz 2.11GHz
    * 32GB RAM
* Avem asadar, un producator si 7 consumatori la fiecare executie.

## Rulare
* Pentru variantele pthreads, MPI si OpenMP se procedeaza dupa cum urmeaza:
    * Se executa comanda **make**, dupa care **make run ARGS=<dim>**, unde dim este dimensiunea datelor de intrare.
* Pentru varianta MPI-OpenMP
    * Se executa comanda **make**, dupa care **make run ARGS="<dim> <num_threads_per_process>"**.
    * Rezultatul se va gasi in fisierul *data.out*.

## Timpi
* S-a folosit scriptul *profiling.sh* pentru a rula programul de mai multe ori si a calcula o medie a timpilor obtinuti.
    * **rulare**: ./profiling.sh *dim*, unde *dim* este exponentul lui 2 pentru dimensiunea datelor de intrare
        * **exemplu**: *./profiling.sh 20* va rula scriptul pentru o dimensiune a datelor de intrare egala cu 2^20
    * * fiecare proces(nod) are 4 thread-uri pentru varianta MPI-OpenMP

* In urma rularii de un numar semnificativ de ori, s-au obtinut rezultatele de mai jos:

| dimensiune input |  pthreads |    MPI   | MPI-OpenMP |  OpenMP  |
|:----------------:|:---------:|:--------:|:----------:|:--------:|
|     1.048.576    |  3.60929  |  0.47137 |   0.40416  |  0.29317 |
|     2.097.152    |  7.19864  |  1.69562 |   0.82059  |  0.62330 |
|     4.194.304    |  16.45677 |  2.54125 |   1.66122  |  1.26392 |
|     8.388.608    |  37.22144 |  3.60969 |   3.26145  |  2.50559 |
|    16.777.216    |  78.00049 |  6.97344 |   6.36677  |  5.00413 |
|    33.554.432    | 163.40278 | 16.76264 |  16.39661  | 11.43295 |

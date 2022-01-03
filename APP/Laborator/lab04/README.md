# Laborator 4 - Introducere in MPI

## How to run
    * se adauga in ~/.bashrc pe fep urmatoarele 2 linii:
        * module load compilers/gnu-5.4.0
        * module load libraries/openmpi-2.0.1-gcc-5.4.0
    * se compileaza cu mpicc -w -o main file.c
    * se scrie scriptul run.sh pentru a specifica pe cate slot-uri ruleaza programul
    * se submite un job-ul pe cluster
        * qsub -q all.q -cwd ./run.sh 
        * qsub -q all.q -pe openmpi nProcesses -cwd ./run.sh
    * outputul se afla in run.sh.o###, iar erorile se afla in run.sh.e###

## Exercitii pdf

* **Exercitiul 1** - HelloWorld in MPI
    * se initializeaza environment-ul de MPI, se determina numarul de procese din comunicator, respectiv rank-ul procesului curent si se afiseaza un mesaj corespunzator
* **Exercitiul 2** - Suma vector MPI
    * se trimite un chunk de elemente fiecarui proces, acesta va calcula suma partiala, va trimite rezultatul catre master care va aduna toate rezultatele partiale si va afisa suma finala
* **Exercitiul 3** - Suma vector * coef MPI
    * la fel ca la exercitiul precedent, numai ca se foloseste un MPI_Bcast pentru a trimite tuturor proceselor valoarea coeficientului
    * dupa in loc de a aduna suma in master, se aduna suma * coef
* **Exercitiul 4** - Suma vector MPI folosind MPI_Scatter si MPI_Gather
    * se foloseste MPI_Scatter pentru a trimite chunk-uri de elemente catre celelalte procese
    * fiecare proces calculeaza bucata sa si trimite suma catre MASTER
    * procesul MASTER aduna toate sumele partiale si afiseaza suma finala

## Exercitii activitate laborator
* **Exercitiul 1** - HelloWorld in MPI
    * se initializeaza environment-ul de MPI, se determina numarul de procese din comunicator, respectiv rank-ul procesului curent si se afiseaza un mesaj corespunzator
* **Exercitiul 2** - Bandwidth Timing Test
    * exemplu de trimitere/primire mesaje intre procese
    * numarul de procese trebuie sa fie par
    * se folosesc functiile MPI_Send si MPI_Recv pentru trimitere, respectiv primire de data intre procese
    * se realizeaza calcule pentru bandwith bazate pe dimensiunea mesajelor si a timpilor
* **Exercitiul 3** - Round Trip Latency Timing Test
    * se calculeaza latenta intre trimiterea si primirea unor mesaje intre procese
* **Exercitiul 4** - Matrix Multiply
    * se trimit chunk-uri din matrice catre workeri (toate procesele in afara de MASTER)
    * ficare worker trimite bucata calculata catre MASTER
    * procesul MASTER primeste de la fiecare worker bucata calculata de catre acesta si afiseza rezultatul final
* **Exercitiul 5** - pi Calculation
    * exemplu de comunicare point-to-point pentru calcularea numarului pi
    * se foloseste algoritmul "dartboard"
    * colectarea rezultatelor se realizeaza prin apelurile functilor de send si receive
    * procesul MASTER aduna datele de la fiecare worker si afiseaza rezultatul final
    
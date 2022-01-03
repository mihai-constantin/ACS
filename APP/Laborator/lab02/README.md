# Laborator 2

## Exercitii pdf
* **Exercitiul 1** - Politica de scheduling dynamic vs static
    * dynamic\
        [mihai.constantin98@fep7-1 lab02]$ ./ex1\
        Number of threads = 4\
        Execution time: 0.063621\
    Timp de executie aproximativ: **0.06s**

    * static\
        [mihai.constantin98@fep7-1 lab02]$ ./ex1 \
        Number of threads = 4\
        Execution time: 0.0377946\
        Timp de executie aproximativ: **0.03s**

    Politica statica are o imbunatatire semnificativa fata de cea dinamica, deoarece task-ul de fata nu au un timp variabil de executie.\
    Se realizeaza o adunare de vectori, deci timpul este constant, de unde si imbunatatirea pentru varianta statica.

* **Exercitiul 2** - Calcularea lui pi folosind reduction
    * varianta secventiala\
        [mihai.constantin98@fep7-1 lab02]$ ./ex2\
        Execution time 0.164419\
        The computed value of pi is 3.141593\
    Timp de executie aproximativ: **0.16s**

    * varianta paralela folosind reduction\
        [mihai.constantin98@fep7-1 lab02]$ ./ex2_reduction\
        Execution time 0.0547537\
        The computed value of pi is 3.141593\
    Timp de executie aproximativ: **0.055s**

    Varianta folosind reduction are o imbunatatire de 3 ori mai mare din punct de vedere al timpului de executie.

* **Exercitiul 3** - Determinarea numarului de caractere A-Z din continutul tuturor fisierelor din directorul files
    * se ruleaza script-ul gen_files.sh pentru a se genera fisierele in care se vor cauta caracterele A-Z
    * varianta secventiala\
        Execution time 0.137487s
    * varianta paralela folosind OpenMP
        Execution time 0.0681526

## Exercitii laborator
* **Exercitiul 1** - Marire performanta pentru inmultire de matrice
    * Am inlocuit regiunile in care erau initializate matricele pe baza de scheduling cu directive de sectiuni.
    * Se observa o usoara imbunatatire din punct de vedere al timpului.
* **Exercitiul 2** - Marire performanta pentru inmultire de matrice prin inlocuirea politicii de scheduling
    * Am modificat politica de scheduling din static in **auto** pentru a imbunatati astfel performantele.
    * De asemenea, nu mai este nevoie de o valoare predefinita pentru un chunk size.
* **Exercitiul 3** - Inmultirea unei matrice cu un vector pentru 1, 2, 4 si 8 thread-uri
    * Am modificat in Makefile astfel incat programul sa ruleze pe 1, 2, 4 sau 8 threaduri (PROCS = 1 2 4 8)
    * Rulare: make omp; ./mxv_omp.exe
    * Pe masura ce numarul de threaduri creste, se observa o crestere a performantei.
* **Exercitiul 4** - Schimbarea politicii de scheduling pentru exercitiul 3
    * Am adaugat in fisierul mxv_col_omp.c o politica dinamica de scheduling

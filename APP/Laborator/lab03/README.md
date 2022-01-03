# Laborator 3

* **Exercitiul 1** - Sections
    * bucata de cod din cadrul unei directive sections va fi executata de catre un singur thread
* **Exercitiul 2** - Adaugare directiva sections
    * Se observa o imbunatatire de aproximativ 0.5s pentru varianta care foloseste sections fata de varianta secventiala pentru o dimensiune a problemei de 10^8.
* **Exercitiul 3** - Marire performanta pentru inmultire de matrice
    * Am inlocuit regiunile in care erau initializate matricele pe baza de scheduling cu directive de sectiuni.
    * Se observa o usoara imbunatatire din punct de vedere al timpului.
* **Exercitiul 4** - Marire performanta pentru inmultire de matrice prin inlocuirea politicii de scheduling
    * Am modificat politica de scheduling din static in **auto** pentru a imbunatati astfel performantele.
    * De asemenea, nu mai este nevoie de o valoare predefinita pentru un chunk size.
* **Exercitiul 5** - Inmultirea unei matrice cu un vector pentru 1, 2, 4 si 8 thread-uri
    * Am modificat in Makefile astfel incat programul sa ruleze pe 1, 2, 4 sau 8 threaduri (PROCS = 1 2 4 8)
    * Rulare: make omp; ./mxv_omp.exe
    * Pe masura ce numarul de threaduri creste, se observa o crestere a performantei.
* **Exercitiul 6** - Schimbarea politicii de scheduling pentru exercitiul 3
    * Am adaugat in fisierul mxv_col_omp.c o politica dinamica de scheduling

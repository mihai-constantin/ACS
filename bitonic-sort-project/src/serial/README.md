# Bitonic Sort - varianta seriala

## Detalii implementare
* Algoritmul are 2 pasi pentru a sorta o secventa de dimensiune 2^k
    * transformarea secventei intr-o secventa bitonica (secventa de forma x0 <= x1 <= ... <= xi >= xi+1 ... >= xn-1)
        * se considera fiecare 2 elemente alaturate din vector o secventa bitonica si se aplica o sortare bitonica pe fiecare pereche de elemente
        * la pasii urmatori se vor considera secvente de dimensiune 4, dupa aceea de dimensiune 8 s.a.m.d
    * crearea vectorului sortat pe baza secventei
        * se realizeaza comparatii intre perechi de numere situate la distanta de lungime putere a lui 2, incepand cu lungimea 2^k-1 pana la lungime 2
        * este practic, ultimul apel din recursivitate: bitonic_sort(a, 0, 2^k, 1) -> bitonic_merge(a, 0, 2^k, 1), daca vrem sa sortam crescator

## Timp rulare - testat pe fep
* In urma rularii de un numar semnificativ de ori, s-au obtinut urmatoarele rezultate:
    * pentru un vector de dimensiune 2^20, o medie de 1.318s
    * pentru un vector de dimensiune 2^21, o medie de 2.831s
    * pentru un vector de dimensiune 2^22, o medie de 6.182s
    * pentru un vector de dimensiune 2^23, o medie de 13.272s
    * pentru un vector de dimensiune 2^24, o medie de 28.545s
    * pentru un vector de dimensiune 2^25, o medie de 61.401s

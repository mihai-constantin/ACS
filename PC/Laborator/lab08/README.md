# Laborator 8 - Pointeri. Abordarea lucrului cu tablouri folosind pointeri.

* operatorul de referentiere &
* operatorul de deferentiere *
* pointeri la date
* pointeri la tablouri
* pointeri in functii
* **pointeri la functii**

## Exercitii lab
* afisare numar in format little/big endian (in functie de arhitectura proprie)
* prelucrare siruri de caractere, folosind functii specifice
* folosire pointer la functie

## Exercitii
* Sa se inverseze elementele unui vector utilizand o parcurgere cu 2 pointeri (unul de la inceput si unul de la final). 
Antetul functiei este **void reverse(int *v, int n)**. Nu se va permite accesul elementelor folosind operatorul [].

    | Input          | Output    |
    |----------------|-----------|
    | 5<br>1 2 3 4 5 | 5 4 3 2 1 |

* Se dau 2 vectori de numere intregi. Sa se insereze al doilea vector in primul vector incepand cu o pozitie data.
Antetul functiei este **void insert(int *v1, int *n, int *v2, int m, int pos)**. 
Vectorul v1 are n elemente si vectorul v2 are m elemente (de asemenea, numarul de elemente pentru v1 trebuie modificat dupa apelul functiei insert). Daca pos == 0, se va insera la inceputul vectorului v1, daca pos == n, se va insera la sfarsitul acestuia.
Nu se va permite accesul elementelor folosind operatorul [].

    | Input                           | Output        |
    |---------------------------------|---------------|
    | 4<br>1 2 3 4<br>3<br>5 6 7<br>1 | 1 5 6 7 2 3 4 |

La finalul subprogramului, n devine 7.

* Bonus: QuickSort

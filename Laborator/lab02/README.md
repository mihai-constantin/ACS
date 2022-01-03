# Laborator 2 - Tipuri de date. Operatori. Masurarea timpului de executie. Functii matematice

* comportamentul descriptorilor
* diverse cazuri de **overflow**
* masurarea timpului de executie a programului
* generare de numere aleatoare

## Exercitii
* Se dau doua intervale orare specificate prin ore, minute si secunde (hh:mm:ss). Determinati numarul de ore, minute si secunde dintre cele doua intervale. Se considera timpul de la primul interval la al doilea.

    | Input             | Output   |
    |-------------------|----------|
    | 23:00:00 01:00:00 | 2 0 0    |
    | 17:40:21 04:23:54 | 10 43 33 |

* Determinati punctul de intersectie a doua drepte (daca exista). Daca nu exista, determinati daca dreptele coincid (se intersecteaza intr-o infinitate de puncte) sau daca sunt paralele (nu se intersecteaza). (Ec. dreptei: ax + by + c = 0).

    | Input          | Output                                     |
    |----------------|--------------------------------------------|
    | 1 2 3 4 5 6    | Punctul de intersectie: 1.000000 -2.000000 |
    | 3 8 12 6 16 24 | Cele doua linii coincid.                   |
    | 3 0 3 4 0 8    | Cele doua linii sunt paralele.             |

# Laborator 10 - Prelucrarea sirurilor de caractere. Functii

* gets, fgets, puts
* **memset**, **memmove**, **memcpy**
* strlen
* strcpy, strncpy
* strcat, strncat
* strcmp
* strchr, strrchr
* strstr
* strdup
* strtok

## Exercitii lab
* ordonare alfabetica/in functie de numarul de caractere a unui sir de cuvinte
* determinare numar de aparitii al unui cuvant dintr-o propozitie
* determinare propozitie palindroma

## Exercitii
* Se citeste de la tastatura un cuvant format din litere mici si mari ale alfabetului englez (fara whitespace) si un caracter (cuvantul are mai putin de 100 de caractere). Sa se inlocuiasca fiecare aparitie a caracterului in cuvantul intial cu numarul de aparitii ale caracterului pana in momentul respectiv.

    | Input             | Output       |
    |-------------------|--------------|
    | Antananarivo<br>a | Ant1n2n3rivo |

* Se citeste de la tastatura un cuvant format din litere mari, litere mici si cifre. Sa se afiseze cel mai lung prefix al cuvantului diferit de cuvantul intreg, care este si sufix si acestuia. Un prefix al unui string este un substring (pozitii consecutive) care incepe pe pe prima pozitie. Un sufix al unui string este un substring care se termina pe ultima pozitie. Atentie, nu consideram prefixul egal cu intreg cuvantul.

    | Input       | Output |
    |-------------|--------|
    | abracadabra | abra   |

* Folosind funcţiile din <string.h> înlocuiţi într-un text dat o secventă de caractere cu altă secvenţă de caractere, date la intrare.

# Laborator 7 - MPI

* **Suma vector MPI**
    * se trimite un chunk de elemente fiecarui proces, acesta va calcula suma partiala, va trimite rezultatul catre master care va aduna toate rezultatele partiale si va afisa suma finala
* **Suma vector MPI folosind MPI_Scatter si MPI_Gather**
    * se foloseste MPI_Scatter pentru a trimite chunk-uri de elemente catre celelalte procese
    * fiecare proces calculeaza bucata sa si trimite suma catre MASTER
    * procesul MASTER aduna toate sumele partiale si afiseaza suma finala
    
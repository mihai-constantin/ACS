# Laborator 1 - Modele teoretice de calculatoare paralele

* Algoritmul de inmultire secventiala de matrici
    * gcc secv.c -o main -Wall
    * Matricea C se calculeaza clasic, conform cu formula matematica.
* Algoritmul CRCW-PRAM cu n^3 procesoare pentru inmultire de matrici
    * gcc crcw.c -o main -Wall -lpthread
    * CRCW - Concurrent-Read Concurrent-Write
    * Algoritmul are doua etape:
        * Fiecare procesor P(i,j,k) calculeaza in paralel produsul A[i][j] * B[j][k].
        * Se face scrierea concurenta a procesoarelor in locatia C[i][j] a termenilor A[i][k] * B[k][j], k = [0...n-1], care se insumeaza.
* Algoritmul CREW-PRAM cu n^3 procesoare pentru inmultire de matrici
    * gcc crew.c -o main -Wall -lpthread -lm
    * CREW - Concurrent-Read Exclusive Write
    * Algoritmul are doua etape:
        * Fiecare procesor P(i,j,k) calculeaza in paralel produsul A[i][j] * B[j][k].
        * Reducere prin insumare.

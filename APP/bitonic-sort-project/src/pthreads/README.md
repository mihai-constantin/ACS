# Bitonic Sort - varianta paralela pthreads

## Detalii implementare
* abordare similara cu varianta secventiala
* se creeaza din sirul dat o secventa bitonica (secventa de forma x0 <= x1 <= ... <= xi >= xi+1 ... >= xn-1)
* se realizeaza comparatii intre perechi de numere situate la distanta de lungime putere a lui 2, incepand cu lungimea 2^k-1 pana la lungime 2
* se creeza un thread pentru fiecare subvector luat in considerare de-a lungul algoritmului pentru a mari eficienta paralelismului
* numarul de thread-uri create este contorizat de variabila thread_count

## Timp rulare
* In urma rularii de un numar semnificativ de ori cu **16 thread-uri**, s-au obtinut urmatoarele rezultate:
    * pentru un vector de dimensiune 2^20, o medie de 0.443s
    * pentru un vector de dimensiune 2^21, o medie de 0.925s
    * pentru un vector de dimensiune 2^22, o medie de 1.889s
    * pentru un vector de dimensiune 2^23, o medie de 4.205s
    * pentru un vector de dimensiune 2^24, o medie de 8.701s
    * pentru un vector de dimensiune 2^25, o medie de 18.267s
    
# Bitonic Sort - varianta paralela OpenMP

## Detalii implementare
* Deoarece '#pragma omp parallel' realizeaza un numar mare de fork-uri si join-uri, este
important sa stim cand trebuie sa folosim functia de sortare paralela a
secventelor si cand trebuie sa o folosim pe cea seriala (pentru a nu se
crea un overhead care nu este necesar).
    * Atunci cand suntem deja in interiorul unei secvente de cod
    paralelizata cu '#pragma omp parallel' si trebuie sa apelam functia de sortare
    a unei secvente din vector, vom alege functia secventiala (deoarece toate
    core-urile sunt deja ocupate cu alte secvente)
    * Atunci cand suntem intr-o secventa de cod seriala, putem apela metoda de
      sortare a secventelor paralela, deoarece core-urile nu sunt ocupate cu
      alte computatii

## Timp rulare - testat pe fep
* In urma rularii de un numar semnificativ de ori, s-au obtinut urmatoarele rezultate:
    * dimensiune vector: 2^20 | timp mediu de executie: 0.585s | speedup: 2.252
    * dimensiune vector: 2^21 | timp mediu de executie: 1.282s | speedup: 2.208
    * dimensiune vector: 2^22 | timp mediu de executie: 2.523s | speedup: 2.450
    * dimensiune vector: 2^23 | timp mediu de executie: 5.609s | speedup: 2.366
    * dimensiune vector: 2^24 | timp mediu de executie: 12.148s | speedup: 2.349
    * dimensiune vector: 2^25 | timp mediu de executie: 24.963s | speedup: 2.459

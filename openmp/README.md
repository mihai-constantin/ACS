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

## Timp rulare
* In urma rularii de un numar semnificativ de ori, s-au obtinut urmatoarele rezultate:
    * dimensiune vector: 2^20 | timp mediu de executie: TODO | speedup: TODO
    * dimensiune vector: 2^21 | timp mediu de executie: TODO | speedup: TODO
    * dimensiune vector: 2^22 | timp mediu de executie: TODO | speedup: TODO
    * dimensiune vector: 2^23 | timp mediu de executie: TODO | speedup: TODO
    * dimensiune vector: 2^24 | timp mediu de executie: TODO | speedup: TODO
    * dimensiune vector: 2^25 | timp mediu de executie: TODO | speedup: TODO

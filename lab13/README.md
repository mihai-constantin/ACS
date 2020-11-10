# Laborator 13 - OpenMP

* **Suma vector OpenMP**
    * se ruleaza programul cu prim argument numarul de thread-uri, respectiv cu dimensiunea vectorului pentru care se calculeaza suma elementelor pentru al doilea argument
    * se initializeaza elementele vectorului
    * se seteaza numarul de thread-uri folosind metoda *omp_set_num_threads()*
    * se folosesc urmatoarele directive pentru paralelizare si evitarea conflictelor din zona critica:
        * #pragma omp parallel for
        * #pragma omp critical
    * se verifica suma calculata in mod paralel cu suma calculata secvential si se afiseaza un mesaj corespunzator
    
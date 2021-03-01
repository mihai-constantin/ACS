# Laborator 12 - pthreads

* **Suma vector pthreads**
    * se ruleaza programul cu prim argument numarul de thread-uri, respectiv cu dimensiunea vectorului pentru care se calculeaza suma elementelor
    * se initializeaza elementele vectorului
    * fiecarui thread i se va asocia o bucata din vector, acesta va calcula suma si o va pune in s[thread_id]
    * dupa join-ul tuturor thread-urilor, se va calcula suma totala, adunand fiecare element din vectorul s
    * se verifica suma calculata in mod paralel cu suma calculata secvential si se afiseaza un mesaj corespunzator
    
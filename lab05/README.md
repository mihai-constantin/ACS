# Laborator 5 - Introducere in pthreads

* Modelul boss-workers
    * model bazat pe faptul ca un thread coordoneaza munca celorlalte n-1 thread-uri
        * thread-ul boss obtine "munca" pe care o pune intr-o coada din care celelalte thread-uri pot alege ce sa faca
    * S-au obtinut urmatorii timpi pentru un numar de 10^6 elemente.
        * 8.767s pentru 8 thread-uri si o capacitate de 16 pentru coada
        * 8.027s pentru 8 thread-uri si o capacitate de 8 pentru coada
        * 14.139s pentru 16 thread-uri si o capacitate de 16 pentru coada

    * De remarcat faptul ca daca avem 2^20 (~10^6) elemente, obtinem timpi relativ mai mici pe fiecare caz
        * 7.885s pentru 8 thread-uri si o capacitate de 16 pentru coada
        * 7.898s pentru 8 thread-uri si o capacitate de 8 pentru coada
        * 11.795s pentru 16 thread-uri si o capacitate de 16 pentru coada

* Modelul work-crew
    * model similar cu modelul boss-workers, numai ca si thread-ul boss munceste
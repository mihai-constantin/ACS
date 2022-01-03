## 2 clienti - operatii de baza

* Se deschid 2 terminale, in continuare notate cu T1 si T2
* Serverul va afisa dupa fiecare operatie configuratia listei de useri autentificati in sistem, precum si continutul bazei de date.
* Operatiile sunt descrise mai jos
    * T1: login misu
        * response: User misu logged in successfully with id = 1!
    * T2: login oana
        * response: User oana logged in successfully with id = 2!
    * T1: load
        * response: misu.rpcdb file was created successfully!
    * T2: load
        * response: oana.rpcdb file was created successfully!
    * T1: add 1110 3 1.0 2.0 3.0
        * response: New entry with id = 1110 was added successfully into database!
    * T1: add 2220 4 1.0 2.0 3.0 4.0
        * response: New entry with id = 2220 was added successfully into database!
    * T1: update 1110 2 1.0 2.0
        * response: Entry with id = 1110 was update successfully into database!
    * T1: store
        * response: Store was successful!
    * T2: add 3330 2 1.2 3.2
        * response: New entry with id = 3330 was added successfully into database!
    * T2: add 4440 3 1.5 2.5 3.5
        * response: New entry with id = 4440 was added successfully into database!
    * T2: del 4440
        * response: Entry with id = 4440 successfully deleted from client 2!
    * T2: store
        * response: Store was successful!
    * T2: logout
        * response: User oana was logged out!
    * T1: logout
        * reponse: User misu was logged out!
    * T2: exit
        * reponse: Goodby!
    * T1: exit
        * reponse: Goodby!

In urma celor 2 operatii de store, continutul celor 2 fisire este urmatorul:

    | misu.rpcdb | 1110 2 1.000000 2.000000<br>2220 4 1.000000 2.000000 3.000000 4.000000 |
    |------------|------------------------------------------------------------------------|
    | oana.rpcdb | 3330 2 1.200000 3.200000                                               |
    
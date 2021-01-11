## 2 clienti - operatii de baza + handler-uri de erori

* Se deschid 2 terminale, in continuare notate cu T1 si T2
* Serverul va afisa dupa fiecare operatie configuratia listei de useri autentificati in sistem, precum si continutul bazei de date.
* In acest moment avem fisierele misu.rpcdb si oana.rpcdb cu informatiile descrise de la testul 1.
* Operatiile sunt descrise mai jos
    * T1
        * login misu
            * User misu logged in successfully with id = 1!
        * load
            * Get data from misu.rpcdb file!
        * add 1110 3 1.1 2.2 3.3
            * Entry with id = 1110 was update successfully into database!
        * del 3330
            * Client [1] has no entry with id = 3330
        * del 2220
            * Entry with id = 2220 successfully deleted from client 1!
        * read 1110
            * Entry found: 1110 31.100000 2.200000 3.300000 
        * read 2220
            * No entry with id = 2220 was found!
        * get_stat 1110
            * minim: 1.100000
        * maxim: 3.300000
            * medie: 2.200000
            * mediana: 2.200000
        * get_stat 1115
            * Client [1] has no entry with id = 1115
        * get_stat_all
            * [get_stat_all]
            * Entry [0]
            * minim: 1.100000
            * maxim: 3.300000
            * medie: 2.200000
            * mediana: 2.200000
        * add 3330 4 1.1 2.2 3.3 4.4
            * New entry with id = 3330 was added successfully into database!
        * store
            * Store was successful!
        * logout
            * User misu was logged out!
        * exit
            * Goodby!

    * T2
        * login oana
            * User oana logged in successfully with id = 2!
        * load
            * Get data from oana.rpcdb file!
        * read 3335
            * No entry with id = 3335 was found!
        * read 3330
            * Entry found: 3330 21.200000 3.200000 
        * del 3330
            * Entry with id = 3330 successfully deleted from client 2!
        * read 3330
            * No entry with id = 3330 was found!
        * add 3330 4 1.1 2.2 3.3 4.4
            * New entry with id = 3330 was added successfully into database!
        * read 3330
            * Entry found: 3330 41.100000 2.200000 3.300000 4.400000 
        * get_stat 3335
            * Client [2] has no entry with id = 3335
        * get_stat 3330
            * minim: 1.100000
            * maxim: 4.400000
            * medie: 2.750000
            * mediana: 2.750000
        * get_stat_all
            * [get_stat_all]
            * Entry [0]
            * minim: 1.100000
            * maxim: 4.400000
            * medie: 2.750000
            * mediana: 2.750000
        * update 3335 1 2 
            * New entry with id = 3335 was added successfully into database!
        * update 3335 2 1 2
            * Entry with id = 3335 was update successfully into database!
        * add 3330 1 2
            * Entry with id = 3330 was update successfully into database!
        * store
            * Store was successful!
        * logout
            * User oana was logged out!
        * exit
            * Goodby!

In urma celor 2 operatii de store, continutul celor 2 fisire este urmatorul:

    | misu.rpcdb | 1110 3 1.100000 2.200000 3.300000<br>3330 4 1.100000 2.200000 3.300000 4.400000 |
    |------------|---------------------------------------------------------------------------------|
    | oana.rpcdb | 3330 1 2.000000<br>3335 2 1.000000 2.000000                                     |
    
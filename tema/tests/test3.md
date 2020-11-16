## 2 clienti - functionalitate completa

* Se deschid 2 terminale, in continuare notate cu T1 si T2
* Serverul va afisa dupa fiecare operatie configuratia listei de useri autentificati in sistem, precum si continutul bazei de date.
* In acest moment avem fisierele misu.rpcdb si oana.rpcdb cu informatiile descrise de la testul 2.
* Operatiile sunt descrise mai jos
    * T1
        login misu
        User misu logged in successfully with id = 1!
        add 1110 2 1 2
        First use load command!
        load
        Get data from misu.rpcdb file!
        get_stat_all
        [get_stat_all]
        Entry [0]
        minim: 1.100000
        maxim: 3.300000
        medie: 2.200000
        mediana: 2.200000
        Entry [1]
        minim: 1.100000
        maxim: 4.400000
        medie: 2.750000
        mediana: 2.750000
        get_stat 1110
        minim: 1.100000
        maxim: 3.300000
        medie: 2.200000
        mediana: 2.200000
        get_stat 3330
        minim: 1.100000
        maxim: 4.400000
        medie: 2.750000
        mediana: 2.750000
        get_stat 3331
        Client [1] has no entry with id = 3331
        del 3332
        Client [1] has no entry with id = 3332
        del 3330
        Entry with id = 3330 successfully deleted from client 1!
        get_stat_all
        [get_stat_all]
        Entry [0]
        minim: 1.100000
        maxim: 3.300000
        medie: 2.200000
        mediana: 2.200000
        add 2220 4 1.1 2.2 3.3 4.4
        New entry with id = 2220 was added successfully into database!
        update 3330 2 1 2
        New entry with id = 3330 was added successfully into database!
        exit
        User must be logged out!
        logout
        User misu was logged out!
        exit
        Goodby!
    * T2
        login oana
        User oana logged in successfully with id = 2!
        load
        Get data from oana.rpcdb file!
        get_stat_all
        [get_stat_all]
        Entry [0]
        minim: 2.000000
        maxim: 2.000000
        medie: 2.000000
        mediana: 2.000000
        Entry [1]
        minim: 1.000000
        maxim: 2.000000
        medie: 1.500000
        mediana: 1.500000
        add 4440 3 4.5 4.6 10.2
        New entry with id = 4440 was added successfully into database!
        get_stat_all
        [get_stat_all]
        Entry [0]
        minim: 2.000000
        maxim: 2.000000
        medie: 2.000000
        mediana: 2.000000
        Entry [1]
        minim: 1.000000
        maxim: 2.000000
        medie: 1.500000
        mediana: 1.500000
        Entry [2]
        minim: 4.500000
        maxim: 10.200000
        medie: 6.433333
        mediana: 4.600000
        get_stat 4440
        minim: 4.500000
        maxim: 10.200000
        medie: 6.433333
        mediana: 4.600000
        del 3331
        Client [2] has no entry with id = 3331
        del 4440
        Entry with id = 4440 successfully deleted from client 2!
        add 3330 2 2 3
        Entry with id = 3330 was update successfully into database!
        get_stat 3330
        minim: 2.000000
        maxim: 3.000000
        medie: 2.500000
        mediana: 2.500000
        exit
        User must be logged out!
        logout
        User oana was logged out!
        exit
        Goodby!

In urma celor 2 operatii de store, continutul celor 2 fisire este urmatorul:

    | misu.rpcdb | 1110 3 1.100000 2.200000 3.300000 <br>3330 4 1.100000 2.200000 3.300000 4.400000 |
    |------------|----------------------------------------------------------------------------------|
    | oana.rpcdb | 3330 1 2.000000 <br>3335 2 1.000000 2.000000                                     |
    
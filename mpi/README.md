# Bitonic Sort - varianta paralela MPI

## Detalii implementare
* Deoarece mpi este un mod de paralelizare eficient se foloseste paralelizarea pe
intreg algoritmul. Am facut 2 metode de comparare in functie de modul in care se
face sortarea, ascendent sau descendent.
    * Atunci cand alegem metoda CompareLow, se obtin numerele mai mici decat maximul
    curent din procesul pereche care se calculeaza ca process_rank ^ (1 << j), unde
    j este bitul de comparatie care variaza intre [0, log(numar procesoare)).
    * Atunci cand alegem metoda CompareHigh, se obtin valorile mai mari decat minimul
    curent din procesul pereche.

## Detalii rulare
module load libraries/openmpi-2.0.1-gcc-5.4.0 compilers/gnu-5.4.0
mpirun -np 4 --mca btl_tcp_if_include eth0 ./bitonic_sort_mpi < power of 2 >

## Timp rulare - testat pe fep
* In urma rularii de un numar semnificativ de ori, s-au obtinut urmatoarele rezultate:
    * dimensiune vector: 2^20 | timp mediu de executie: 0.125s | speedup: 10.544
    * dimensiune vector: 2^21 | timp mediu de executie: 0.234s | speedup: 12.098
    * dimensiune vector: 2^22 | timp mediu de executie: 0.509s | speedup: 12.145
    * dimensiune vector: 2^23 | timp mediu de executie: 1.123s | speedup: 11.818
    * dimensiune vector: 2^24 | timp mediu de executie: 2.218s | speedup: 12.869
    * dimensiune vector: 2^25 | timp mediu de executie: 4.516s | speedup: 13.596

# Bitonic Sort - varianta paralela hybrid (mpi + openmp)

## Detalii implementare
Implementarea este la fel ca cea de la MPI, la care am adaugat paralelizarea
for-urilor din fiecare proces, folosind OpenMP. Pentru a rezolva problema
break-urilor in OpenMP am folosit constructia "#pragma omp cancel for".

## Detalii rulare
module load libraries/openmpi-2.0.1-gcc-5.4.0 compilers/gnu-5.4.0
mpirun -np 4 --mca btl_tcp_if_include eth0 ./bitonic_sort_hybrid < power of 2 >

## Timp rulare - testat pe fep
* In urma rularii de un numar semnificativ de ori, s-au obtinut urmatoarele rezultate:
    * dimensiune vector: 2^20 | timp mediu de executie: 0.818s | speedup: 1.611
    * dimensiune vector: 2^21 | timp mediu de executie: 1.613s | speedup: 1.755
    * dimensiune vector: 2^22 | timp mediu de executie: 3.123s | speedup: 1.979
    * dimensiune vector: 2^23 | timp mediu de executie: 6.585s | speedup: 2.015
    * dimensiune vector: 2^24 | timp mediu de executie: 13.222s | speedup: 2.159
    * dimensiune vector: 2^25 | timp mediu de executie: 27.722s | speedup: 2.215

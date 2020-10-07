## Laborator 1 - Introducere in OpenMP

* Pentru a compila cu gcc, se foloseste Makefile-ul.

* Pentru a compila cu SunStudio, se foloseste comanda: cc -xopenmp -xO3 file_name.c -o binary_name. 

    In prealabil, se importa modulul de solaris: module load compilers/solarisstudio-12.5

* conectare la fep: ssh mihai.constantin98@fep.grid.pub.ro

* copiere fisiere de pe local pe fep: scp file_name mihai.constantin98@fep.grid.pub.ro:~/APP (rulat de pe host - mac)

* copiere fisiere de pe fep pe local: scp mihai.constantin98@fep.grid.pub.ro:~/file . (rulat de pe host - mac)
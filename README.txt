CONSTANTIN MIHAI - 321CD

Arhiva are urmatoarea structura:

-> algo.h: contine antetele functiilor folosite in algo.cpp si algo2.cpp
-> algo.cpp: implementarea efectiva pentru determinarea LCA-ului prin parcurgere
			 Euler a arborelui + RMQ
-> algo2.cpp: implementarea efectiva pentru determinarea LCA-ului prin metoda
			  programarii dinamice

-> tester.cpp: cod ce contine o metoda main si alege algoritmul pe care vrem
			   sa il testam

-> in: folder ce contine 10 teste pentru testarea fiecarui algoritm
-> out: folder in care se vor genera output-urile in urma rularii checker-ului
-> ref: teste pentru verificarea corectitunii algoritmilor
-> other_tests: folder ce contine 5 teste .in, respectiv .out folosite pentru
				verificarea suplimentara a algoritmilor propusi

-> Makefile: contine regulile de build_best, build_snd_best, run si clean
-> checker.sh: script ce verifica corectitudinea algoritmilor pe baza testelor
			   propuse + calculeaza timpul executiei programelor

Testele propuse sunt generate respectand urmatoarele cazuri:
-> N << M
	test0.in: N = 100 000, M = 2 000 000
	test1.in: N = 100 000, M = 1 800 000
	test2.in: N = 100 000, M = 1 400 000
	test3.in: N = 100 000, M =   800 000

-> N ~ M 
	test4.in: N = 100 000, M = 100 000
	test5.in: N =  50 000, M =  50 000
	test6.in: N =  10 000, M =  10 000

-> N >> M
	test7.in: N = 60 000, M = 6 000
	test8.in: N = 60 000, M = 1 000
	test9.in: N = 30 000, M = 4 000

Folderul other_tests contine 5 teste cu urmatoarea structura:
-> test0.in: N =  1 000, M = 100
-> test1.in: N = 10 000, M = 100
-> test2.in: N = 40 000, M = 10 000
-> test3.in: N = 50 000, M = 1 000 000
-> test4.in: N = 50 000, M = 5 000
	
IMPORTANT!

Testarea se efectueaza astfel:

$ make build_best -> se genereaza fisierele obiect si executabilul 
					 pentru algo.cpp

$ make build_snd_best -> se genereaza fisierele obiect si executabilul pentru
						 algo2.cpp

$ make run -> se ruleaza checker-ul pentru executabilul curent

Corectitudinea algoritmului se verifica prin compararea fisierelor din folderul
out cu cele din ref.
La fiecare test am calculat si timpul de executie, iar la final am afisat
timpul total al rularii algoritmului pe cele 10 teste.

$ make clean -> se sterg fisierele obiect si executabilul

Exemplu:
$ make build_best
$ make run
$ make build_snd_best
$ make run
$ make clean

Statistici

La rularea de 10 ori a checker-ului pe un sistem Ubuntu 16.04.5 de 64 de biti,
s-au obtinut urmatoarele rezultate:
-> timpul mediu de rulare al primului algoritm (algo.cpp) s-a efectuat in 1.74s
-> timpul mediu de rulare al celui de-al doilea algoritm (algo2.cpp) s-a
   efectuat in 2.4s

 Diferenta de performanta din punct de vedere al timpului pe cele 10 teste 
 propuse este de 0.66s in favoarea primului algoritm. 




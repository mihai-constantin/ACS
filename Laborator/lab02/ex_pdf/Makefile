all: ex1 ex2 ex2_reduction ex3 ex3_openmp

ex1: ex1.c
	gcc -fopenmp $? -o $@ -Wall

ex2: ex2.c
	gcc -fopenmp $? -o $@ -Wall

ex2_reduction: ex2_reduction.c
	gcc -fopenmp $? -o $@ -Wall

ex3: ex3.c
	gcc -fopenmp $? -o $@ -Wall

ex3_openmp: ex3_openmp.c
	gcc -fopenmp $? -o $@ -Wall -lm

.PHNOY: clean
clean:
	rm -f ex1 ex2 ex2_reduction ex3 ex3_openmp

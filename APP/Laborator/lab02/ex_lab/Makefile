all: ex1 ex2

ex1: ex1.c
	gcc -fopenmp $? -o $@ -Wall

ex2: ex2.c
	gcc -fopenmp $? -o $@ -Wall

.PHNOY: clean
clean:
	rm -f ex1 ex2

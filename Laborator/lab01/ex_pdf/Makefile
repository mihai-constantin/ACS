all: variables for sum

variables: variables.c
	gcc -fopenmp $? -o $@ -Wall

for: for.c
	gcc -fopenmp $? -o $@ -Wall

sum: sum.c
	gcc -fopenmp $? -o $@ -Wall

ex1: ex1.c
	gcc -fopenmp $? -o $@ -Wall

ex1-1: ex1-1.c
	gcc -fopenmp $? -o $@ -Wall

ex2: ex2.c
	gcc -fopenmp $? -o $@ -lm -Wall

.PHNOY: clean
clean:
	rm -f variables for sum ex1 ex1-1 ex2

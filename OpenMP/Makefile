all: ex1

ex1: ex1.c
	gcc -fopenmp $? -o $@ -Wall

.PHNOY: clean
clean:
	rm -f ex1

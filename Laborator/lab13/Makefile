all: suma

suma: suma.c
	gcc -fopenmp $? -o $@ -Wall

.PHNOY: clean
clean:
	rm -f suma
	
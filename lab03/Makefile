all: sections ex_sections_secv ex_sections_par matrix_multiplication matrix_multiplication2

sections: sections.c
	gcc -fopenmp $? -o $@ -Wall

ex_sections_secv: ex_sections_secv.c
	gcc -fopenmp $? -o $@ -Wall -lm

ex_sections_par: ex_sections_par.c
	gcc -fopenmp $? -o $@ -Wall -lm

matrix_multiplication: matrix_multiplication.c
	gcc -fopenmp $? -o $@ -Wall -lm

matrix_multiplication2: matrix_multiplication2.c
	gcc -fopenmp $? -o $@ -Wall -lm

.PHNOY: clean
clean:
	rm -f sections ex_sections_secv ex_sections_par matrix_multiplication matrix_multiplication2

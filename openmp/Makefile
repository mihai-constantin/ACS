CC = gcc
CFLAGS = -Wall

build: bitonic_sort_openmp

bitonic_sort_openmp: bitonic_sort_openmp.c
	$(CC) -o bitonic_sort_openmp bitonic_sort_openmp.c $(CFLAGS)

.PHONY : clean
clean :
	rm -f bitonic_sort_openmp
	

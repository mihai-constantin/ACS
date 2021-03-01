CC = mpicc
CFLAGS = -Wall -lm

build: bitonic_sort_mpi

bitonic_sort_mpi: bitonic_sort_mpi.c
	$(CC) -o bitonic_sort_mpi bitonic_sort_mpi.c $(CFLAGS)

.PHONY : clean
clean :
	rm -f bitonic_sort_mpi

CC = mpicc
CFLAGS = -fopenmp -lm

build: bitonic_sort_hybrid

bitonic_sort_mpi: bitonic_sort_hybrid.c
	$(CC) -o bitonic_sort_hybrid bitonic_sort_hybrid.c $(CFLAGS)

.PHONY : clean
clean :
	rm -f bitonic_sort_hybrid

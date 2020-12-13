CC = mpicc -w
CFLAGS = -Wall -lm

all: mpi-openmp
 
mpi-openmp: mpi-openmp.c
	$(CC) -o mpi-openmp mpi-openmp.c $(CFLAGS) -fopenmp

run:
	mpirun -n 8  ./mpi-openmp $(ARGS)

.PHONY: clean
clean:
	rm -f mpi-openmp data.out time.out
	
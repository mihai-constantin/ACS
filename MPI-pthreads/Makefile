CC = mpicc -w
CFLAGS = -Wall -lm

all: mpi-pthreads

mpi-pthreads: mpi-pthreads.c
	$(CC) -o mpi-pthreads mpi-pthreads.c $(CFLAGS) -lpthread

run:
	mpirun -n 8  ./mpi-pthreads $(ARGS)

.PHONY: clean
clean:
	rm -f mpi-pthreads data.out time.out
	
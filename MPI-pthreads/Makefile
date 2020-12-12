CC = mpicc -w
CFLAGS = -Wall -lm

all: demo mpi-pthreads
 
demo: demo.c
	$(CC) -o demo demo.c $(CFLAGS) -lpthread

mpi-pthreads: mpi-pthreads.c
	$(CC) -o mpi-pthreads mpi-pthreads.c $(CFLAGS) -lpthread

run:
	mpirun -n 4  ./mpi-pthreads $(ARGS)

.PHONY: clean
clean:
	rm -f demo mpi-pthreads data.out time.out
	
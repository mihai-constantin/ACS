CC = mpicc -w
CFLAGS = -Wall -lm

all: mpi
 
mpi: mpi.c
	$(CC) -o mpi mpi.c $(CFLAGS)

run:
	mpirun -n 4  ./mpi $(ARGS)

.PHONY : clean
clean :
	rm -f mpi data.out time.out
	
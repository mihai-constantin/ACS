CC = mpicc -w
CFLAGS = -Wall -lm

all: mpi
 
mpi: mpi.c
	$(CC) -o mpi mpi.c $(CFLAGS)

run:
	qsub -q all.q -cwd ./run.sh

.PHONY : clean
clean :
	rm -f mpi run.sh.*
	
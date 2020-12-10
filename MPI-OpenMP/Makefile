CC = mpicc -w
CFLAGS = -Wall -lm

all: mpi-openmp demo
 
mpi-openmp: mpi-openmp.c
	$(CC) mpi-openmp.c -o mpi-openmp $(CFLAGS) -fopenmp

demo: demo.c
	$(CC) demo.c -o demo $(CFLAGS) -fopenmp
	
run:
	qsub -q all.q -pe openmpi*2 8 -cwd ./run.sh $(ARGS)

profile:
	./profiling.sh $(ARGS)

.PHONY: clean
clean:
	rm -f mpi-openmp demo run.sh.*

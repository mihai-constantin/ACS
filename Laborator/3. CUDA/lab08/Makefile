COMPILER=nvcc
LIBS=-lm

all: matrix_multiplication task_gflops example_debug

example_debug:  example_debug.cu
	$(COMPILER) example_debug.cu -o example_debug $(LIBS)

matrix_multiplication: matrix_multiplication_skel.cu
	$(COMPILER) matrix_multiplication_skel.cu -o matrix_multiplication $(LIBS)

task_gflops: task_gflops.cu
	$(COMPILER) task_gflops.cu -o task_gflops $(LIBS)

clean:
	rm -rf matrix_multiplication task_gflops example_debug

COMPILER=nvcc
LIBS=-lm

all: example_dynp example_atomic \
    task1_mem_unified task1_mem_plain \
    task2_no_atomic task2_partial_atomic task2_full_atomic \
    task3_atomic_exch \
    task4_dynp

example_dynp: example_dynp.cu
	$(COMPILER) -arch=sm_35 -rdc=true $^ -o $@ $(LIBS)

example_atomic: example_atomic.cu
	$(COMPILER) $^ -o $@ $(LIBS)

task1_mem_unified: task1_unified.cu
	$(COMPILER) $^ -o $@ $(LIBS)

task1_mem_plain: task1_unified.cu
	$(COMPILER) -DNO_UNIFIED_MEMORY $^ -o $@ $(LIBS)

task2_no_atomic: task2_atomic.cu
	$(COMPILER) -DNO_ATOMIC $^ -o $@ $(LIBS)

task2_partial_atomic: task2_atomic.cu
	$(COMPILER) -DPARTIAL_ATOMIC $^ -o $@ $(LIBS)

task2_full_atomic: task2_atomic.cu
	$(COMPILER) -DFULL_ATOMIC $^ -o $@ $(LIBS)

task3_atomic_exch: task3_atomic_exch.cu
	$(COMPILER) $^ -o $@ $(LIBS)
    
task4_dynp: task4_dynp.cu
	$(COMPILER) -arch=sm_35 -rdc=true  $^ -o $@ $(LIBS)

clean:
	rm -rf example_dynp
	rm -rf example_atomic
	rm -rf task1_mem_unified
	rm -rf task1_mem_plain
	rm -rf task2_no_atomic
	rm -rf task2_partial_atomic
	rm -rf task2_full_atomic
	rm -rf task3_atomic_exch
	rm -rf task4_dynp
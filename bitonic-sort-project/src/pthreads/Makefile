CC = gcc
CFLAGS = -lm -lpthread -Wall

build: bitonic_sort_pthreads

bitonic_sort_pthreads: bitonic_sort_pthreads.c
	$(CC) -o bitonic_sort_pthreads bitonic_sort_pthreads.c $(CFLAGS)

.PHONY : clean
clean :
	rm -f bitonic_sort_pthreads
	
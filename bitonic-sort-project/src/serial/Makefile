CC = gcc
CFLAGS = -Wall

build: bitonic_sort

bitonic_sort: bitonic_sort.c
	$(CC) -o bitonic_sort bitonic_sort.c $(CFLAGS)

.PHONY : clean
clean :
	rm -f bitonic_sort
	
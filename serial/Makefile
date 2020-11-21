CC = g++
CFLAGS = -Wall

build: bitonic_sort

bitonic_sort: bitonic_sort.cpp
	$(CC) -o bitonic_sort bitonic_sort.cpp $(CFLAGS)

.PHONY : clean
clean :
	rm -f bitonic_sort
	
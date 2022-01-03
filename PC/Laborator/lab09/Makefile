CC = gcc
CFLAGS = -Wall

all: vector matrix
 
vector: vector.c
	$(CC) -o vector vector.c $(CFLAGS)

matrix: matrix.c
	$(CC) -o matrix matrix.c $(CFLAGS)

memory-check:
	valgrind --leak-check=full ./$(ARGS)

.PHONY : clean
clean :
	rm -f vector matrix

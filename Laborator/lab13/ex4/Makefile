CC = gcc
CFLAGS = -Wall

all: precomp main

precomp: main.c
	$(CC) -o precomp -E main.c $(CFLAGS) 

main: main.c
	$(CC) -o main main.c $(CFLAGS)

.PHONY : clean
clean :
	rm -f precomp main

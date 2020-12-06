CC = gcc
CFLAGS = -lm -lpthread -Wall

build: pthreads

pthreads: pthreads.c
	$(CC) -o pthreads pthreads.c $(CFLAGS)

.PHONY : clean
clean :
	rm -f pthreads
	
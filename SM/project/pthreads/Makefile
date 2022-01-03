CC = gcc
CFLAGS = -Wall -lm -lpthread

all: pthreads

pthreads: pthreads.o queue.o
	$(CC) $? -o $@ $(CFLAGS)

pthreads.o: pthreads.c queue.h
	$(CC) -c pthreads.c $(CFLAGS)

queue.o: queue.c queue.h
	$(CC) -c queue.c $(CFLAGS)

run:
	./pthreads $(ARGS)

clean:
	rm -f *.o pthreads data.out time.out

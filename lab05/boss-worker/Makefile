CC = gcc
CFLAGS = -Wall -lm -lpthread

build: boss-worker

boss-worker: boss-worker.o queue.o
	$(CC) $? -o $@ $(CFLAGS)

boss-worker.o: boss-worker.c queue.h
	$(CC) -c boss-worker.c $(CFLAGS)

queue.o: queue.c queue.h
	$(CC) -c queue.c $(CFLAGS)

clean:
	rm -f *.o boss-worker

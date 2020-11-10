CC = gcc
CFLAGS = -Wall -lm -lpthread

all: boss-worker work-crew

boss-worker: boss-worker.o queue.o
	$(CC) $? -o $@ $(CFLAGS)

work-crew: work-crew.o queue.o
	$(CC) $? -o $@ $(CFLAGS)

boss-worker.o: boss-worker.c queue.h
	$(CC) -c boss-worker.c $(CFLAGS)

work-crew.o: work-crew.c queue.h
	$(CC) -c work-crew.c $(CFLAGS)

queue.o: queue.c queue.h
	$(CC) -c queue.c $(CFLAGS)

clean:
	rm -f *.o boss-worker work-crew

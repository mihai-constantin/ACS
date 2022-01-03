CC = gcc
CFLAGS = -Wall
LDLIBS = -lm

build: so-cpp

so-cpp: so-cpp.o hashTable.h LinkedList.h util.h
	$(CC) -o so-cpp so-cpp.o $(LDLIBS)

so-cpp.o: so-cpp.c hashTable.h LinkedList.h util.h
	$(CC) $(CFLAGS) -c so-cpp.c -o so-cpp.o

clean:
	rm -f *.o so-cpp
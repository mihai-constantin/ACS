CC = gcc
CFLAGS = -Wall -DHAVE_MATH
LDLIBS = -lm

all: ops

ops: ops.o mul.o add.o
	$(CC) -o ops ops.o mul.o add.o $(LDLIBS)

ops.o: ops.c
	$(CC) $(CFLAGS) -c ops.c $(LDLIBS)

mul.o: mul.c
	$(CC) $(CFLAGS) -c mul.c $(LDLIBS)

add.o: add.c
	$(CC) $(CFLAGS) -c add.c $(LDLIBS)

clean:
	rm -rf *.o ops



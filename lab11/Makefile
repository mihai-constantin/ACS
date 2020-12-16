CC = gcc
CFLAGS = -Wall

all: struct union
 
struct: struct.c
	$(CC) -o struct struct.c $(CFLAGS)

union: union.c
	$(CC) -o union union.c $(CFLAGS)

.PHONY : clean
clean :
	rm -f struct union

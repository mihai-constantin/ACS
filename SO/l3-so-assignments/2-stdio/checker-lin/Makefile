CC = gcc
CFLAGS = -Wall -fPIC

all: libso_stdio.so

libso_stdio.so: so_stdio.o so_stdio.h utils.h
	$(CC) -shared so_stdio.o -o libso_stdio.so

so_stdio.o: so_stdio.c so_stdio.h utils.h
	$(CC) $(CFLAGS) -c so_stdio.c -o so_stdio.o

clean:
	rm -f *.o libso_stdio.so
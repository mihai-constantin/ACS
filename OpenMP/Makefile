CC = gcc
CFLAGS = -Wall -lm

all: open-mp

open-mp: open-mp.c
	$(CC) -fopenmp $? -o $@ $(CFLAGS)

run:
	./open-mp $(ARGS)

.PHNOY: clean
clean:
	rm -f open-mp data.out

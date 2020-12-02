CC = gcc
CFLAGS = -lm -lpthread -Wall

build: suma

suma: suma.c
	$(CC) -o suma suma.c $(CFLAGS)

.PHONY : clean
clean :
	rm -f suma
	
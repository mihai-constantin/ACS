CC = gcc
CFLAGS = -Wall

all: demo strtok ordonare palindrom
 
demo: demo.c
	$(CC) -o demo demo.c $(CFLAGS)

strtok: strtok.c
	$(CC) -o strtok strtok.c $(CFLAGS)

ordonare: ordonare.c
	$(CC) -o ordonare ordonare.c $(CFLAGS)

palindrom: palindrom.c
	$(CC) -o palindrom palindrom.c $(CFLAGS)

.PHONY : clean
clean :
	rm -f demo strtok ordonare palindrom

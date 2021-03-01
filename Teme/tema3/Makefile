# Protocoale de comunicatii
# Tema 3
# CONSTANTIN MIHAI - 321CD

CC=gcc
CFLAGS=-I.

build: client.c requests.c helpers.c
		$(CC) client.c requests.c helpers.c -ljson-c -o client -Wall
		
run: client
		./client

clean:
		rm -f *.o client

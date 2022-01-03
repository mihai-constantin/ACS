CC = gcc
CFLAGS = -Wall -I../utils
HEADERS = ../utils/utils.h

all: server client

server: server.o xfile.o

server.o: server.c $(HEADERS)

client: client.o xfile.o

client.o: client.c $(HEADERS)

xfile.o: xfile.c xfile.h

clean:
	rm -f *.o *~ server client myfifo
# Protocoale de comunicatii
# Tema 2
# Constantin Mihai - 321CD

.PHONY = run_server run_subscriber clean
CFLAGS = -Wall -g

# Portul pe care asculta serverul 
PORT = 1200

# Adresa IP a server-ului
IP_SERVER = 127.0.0.1

# ID Client
ID_CLIENT = 

all: server subscriber

# Compileaza server.c
server: server.cpp
	g++ server.cpp -o server ${CFLAGS}

# Compileaza subscriber.c
subscriber: subscriber.cpp
	g++ subscriber.cpp -o subscriber ${CFLAGS}

# Rulare server
run_server:
	./server ${PORT}

# Rulare subscriber
run_subscriber:
	./subscriber ${ID_CLIENT} ${IP_SERVER} ${PORT}

clean:
	rm -f server subscriber

CC = gcc
TARGET = main

all: build

build: $(TARGET)

$(TARGET): f1.o f2.o
	$(CC) -o $(TARGET) $^

f1.o: f1.c
	$(CC) -c $^

f2.o: f2.c
	$(CC) -c $^

.PHONY: clean
clean:
	rm -rf *~ *.o $(TARGET)

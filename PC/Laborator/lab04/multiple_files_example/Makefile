CC = gcc
TARGET = prog

all: build

build: $(TARGET)

$(TARGET): main.o functii.o
	$(CC) -o $(TARGET) $^

main.o: main.c
	$(CC) -c $^

functii.o: functii.c
	$(CC) -c $^ -o $@

.PHONY: clean
clean:
	rm -rf *~ *.o $(TARGET)

.phony: build run test clean

CC = gcc
CFLAGS= -Wall -std=c99
DEPS = $(wildcard *.h)
OBJ = $(patsubst %.c,%.o,$(wildcard *.c))
EXEC = scoala

build: $(EXEC)
		
$(EXEC):$(OBJ)
	gcc $(CFLAGS) -o $@ $^

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c  $< -o $@ 

run:
	./$(EXEC) $(EXEC).in $(EXEC).out

test:
	valgrind --leak-check=full ./$(EXEC) $(EXEC).in $(EXEC).out

clean:
	rm -f $(EXEC) $(OBJ)

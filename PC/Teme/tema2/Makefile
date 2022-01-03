CC = gcc
CFLAGS = -Wall -Wextra -lm
EXE = alocator
OBJ = alocator.o

build: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(OBJ) -o $(EXE) $(CFLAGS)

$(OBJ): alocator.c
	$(CC) -c alocator.c -o $(OBJ) $(CFLAGS) 

clean:
	rm -f $(EXE) $(OBJ)

CC = gcc
CFLAGS = -Wall -lm
EXE1 = task1
EXE2 = pacman

build: $(EXE1) $(EXE2) 

$(EXE1): task1.c
	$(CC) task1.c -o $(EXE1) $(CFLAGS)

$(EXE2): task2.c
	$(CC) task2.c -o $(EXE2) $(CFLAGS)

clean:
	rm -f $(EXE1) $(EXE2)

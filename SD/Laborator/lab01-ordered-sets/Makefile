CC = gcc
CFLAGS = -Wall
EXE1 = charTest
EXE2 = longTest
HEADER = OrderedSet.h

build:	$(EXE1)	$(EXE2)

$(EXE1): charTest.c $(HEADER)
	$(CC) charTest.c -o $(EXE1) $(CFLAGS)

$(EXE2): longTest.c $(HEADER)
	$(CC) longTest.c -o $(EXE2) $(CFLAGS)

run:
	./$(EXE1)
	./$(EXE2)

clean:
	rm -f $(EXE1) $(EXE2)
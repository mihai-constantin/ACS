.phony: build_best build_snd_best run clean

CC = g++
CFLAGS = -Wall -Wextra -O2
EXE = tester
HEADER = algo.h

build_best: algo.o
	$(CC) $(CFLAGS) algo.o tester.cpp -DALGO1 -o $(EXE)

algo.o: algo.cpp $(HEADER)
	$(CC) algo.cpp $(CFLAGS) -c -o algo.o

build_snd_best: algo2.o
	$(CC) $(CFLAGS) algo2.o tester.cpp -DALGO2 -o $(EXE)

algo2.o: algo2.cpp $(HEADER)
	$(CC) algo2.cpp $(CFLAGS) -c -o algo2.o

run:
	./checker.sh

clean:
	rm -f $(EXE) *.o

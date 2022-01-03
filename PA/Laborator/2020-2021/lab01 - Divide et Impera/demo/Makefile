CC = g++
CFLAGS = -Wall -g -std=c++14

all: binary_search hanoi mergesort

binary_search: binary_search.cpp
	$(CC) $(CFLAGS) $^ -o $@

hanoi: hanoi.cpp
	$(CC) $(CFLAGS) $^ -o $@

mergesort: mergesort.cpp
	$(CC) $(CFLAGS) $^ -o $@

pack: binary_search.cpp mergesort.cpp hanoi.cpp
	zip -r demo-lab02.zip *.cpp Makefile

.PHONY: clean

clean:
	rm -rf *.o binary_search hanoi mergesort *.zip *.dSYM

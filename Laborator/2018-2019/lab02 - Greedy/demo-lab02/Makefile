CC = g++
CFLAGS = -Wall -g -std=c++14

all: cuie spectacole florar

cuie: cuie.cpp
	$(CC) $(CFLAGS) $^ -o $@

spectacole: spectacole.cpp
	$(CC) $(CFLAGS) $^ -o $@

florar: florar.cpp
	$(CC) $(CFLAGS) $^ -o $@

pack: cuie.cpp florar.cpp spectacole.cpp
	zip -r demo-lab02.zip *.cpp Makefile

.PHONY: clean

clean:
	rm -f *.o cuie spectacole florar *.zip

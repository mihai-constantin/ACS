CC = gcc
CFLAGS = -Wall

run: task1 task2 task3 bonus
	./task1
	./task2
	./task3
	./bonus

build: task1.o task2.o task3.o bonus.o
	$(CC) task1.o -o task1
	$(CC) task2.o -o task2
	$(CC) task3.o -o task3
	$(CC) bonus.o -o bonus

task1.o: task1.c bmp_header.h
	$(CC) -c task1.c $(CFLAGS)

task2.o: task2.c bmp_header.h
	$(CC) -c task2.c $(CFLAGS)

task3.o: task3.c bmp_header.h
	$(CC) -c task3.c $(CFLAGS)

bonus.o: bonus.c bmp_header.h
	$(CC) -c bonus.c $(CFLAGS)

clean:
	rm -f *.o task1 task2 task3 bonus



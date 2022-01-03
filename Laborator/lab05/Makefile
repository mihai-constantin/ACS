CC = gcc
CFLAGS = -Wall

all: warm-up min-max-medie selection-sort diferenta ssm
 
warm-up: warm-up.c
	$(CC) -o warm-up warm-up.c $(CFLAGS)

min-max-medie: ex1/min-max-medie.c
	$(CC) -o min-max-medie ex1/min-max-medie.c $(CFLAGS)

selection-sort: selection-sort.c
	$(CC) -o selection-sort selection-sort.c $(CFLAGS)

diferenta: diferenta.c
	$(CC) -o diferenta diferenta.c $(CFLAGS)

ssm: ssm.c
	$(CC) -o ssm ssm.c $(CFLAGS)

.PHONY : clean
clean :
	rm -f warm-up min-max-medie selection-sort diferenta ssm

CC = gcc
CFLAGS = -Wall

all: demo warm-up endianess sir bonus
 
demo: demo.c
	$(CC) -o demo demo.c $(CFLAGS)

warm-up: warm-up.c
	$(CC) -o warm-up warm-up.c $(CFLAGS)

endianess: endianess.c
	$(CC) -o endianess endianess.c $(CFLAGS)

sir: sir.c
	$(CC) -o sir sir.c $(CFLAGS)

bonus: bonus.c
	$(CC) -o bonus bonus.c $(CFLAGS)

.PHONY : clean
clean :
	rm -f demo warm-up endianess sir bonus

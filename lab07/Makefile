CC = gcc
CFLAGS = -Wall

all: sizeof demo exercitii
 
sizeof: sizeof.c
	$(CC) -o sizeof sizeof.c $(CFLAGS)

demo: demo.c
	$(CC) -o demo demo.c $(CFLAGS)

exercitii: exercitii.c
	$(CC) -o exercitii exercitii.c $(CFLAGS) -lm

.PHONY : clean
clean :
	rm -f sizeof demo exercitii

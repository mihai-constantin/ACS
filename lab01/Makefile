CC = gcc
CFLAGS = -Wall
 
hello: hello.c
	$(CC) -o hello hello.c $(CFLAGS)

baze: baze.c
	$(CC) -o baze baze.c $(CFLAGS)

zecimale: zecimale.c
	$(CC) -o zecimale zecimale.c $(CFLAGS)

sume: sume.c
	$(CC) -o sume sume.c $(CFLAGS)

min-max-fabs: min-max-fabs.c
	$(CC) -o min-max-fabs min-max-fabs.c $(CFLAGS) -lm

precizie: precizie.c
	$(CC) -o precizie precizie.c $(CFLAGS) -lm

.PHONY : clean
clean :
	rm -f hello baze zecimale sume min-max-fabs precizie *~
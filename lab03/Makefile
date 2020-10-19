CC = gcc
CFLAGS = -Wall
 
suma_div_max: suma_div_max.c
	$(CC) -o suma_div_max suma_div_max.c $(CFLAGS)

prim: prim.c
	$(CC) -o prim prim.c $(CFLAGS)

ecuatie: ecuatie.c
	$(CC) -o ecuatie ecuatie.c $(CFLAGS) -lm

baze: baze.c
	$(CC) -o baze baze.c $(CFLAGS) -lm

palindrom: palindrom.c
	$(CC) -o palindrom palindrom.c $(CFLAGS)

.PHONY : clean
clean :
	rm -f suma_div_max prim ecuatie baze palindrom

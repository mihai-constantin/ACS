CC = gcc
CFLAGS = -Wall

all: change_defined change_undef
 
change_defined: main.c
	$(CC) -o change_defined main.c $(CFLAGS) -DCHANGE

change_undef: main.c
	$(CC) -o change_undef main.c $(CFLAGS)

.PHONY : clean
clean :
	rm -f change_defined change_undef

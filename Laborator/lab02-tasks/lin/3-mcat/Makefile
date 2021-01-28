CC = gcc
CPPFLAGS = -I../utils
CFLAGS = -Wall -Wextra -g

.PHONY: all clean

all: mcat mcat_xfile

mcat: mcat.o xfile.o

mcat_xfile: mcat_xfile.o xfile.o

mcat.o: mcat.c ../utils/utils.h

mcat_xfile.o: mcat_xfile.c ../utils/utils.h

xfile.o: xfile.c xfile.h

clean:
	-rm -f *.o *~ mcat mcat_xfile

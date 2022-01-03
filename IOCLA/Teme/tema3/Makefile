CC=gcc
CFLAGS=-m32 -fno-stack-protector -nostartfiles -nostdlib -nodefaultlibs
SPEED_O=tema3.o skel_speed.o
SIZE_O=tema3.o skel_size.o
SPEED=tema3_speed
SIZE=tema3_size
TARGETS=$(SPEED) $(SIZE)

all: $(TARGETS)

%.o: %.asm
	nasm -f elf32 $<

$(SPEED): $(SPEED_O)
$(SIZE): $(SIZE_O)

$(SPEED) $(SIZE):
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f tema3_speed skel_speed.o tema3_size skel_size.o

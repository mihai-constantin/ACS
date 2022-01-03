.phony: build test clean

TESTSRC = $(wildcard test*.c)
TEST = $(patsubst %.c,%,$(TESTSRC))

SRC = $(foreach src,$(wildcard *c),$(patsubst test%,,$(src)))
EXEC = $(patsubst %.c,%,$(SRC))
HEADERS = $(wildcard *.h)

CC = gcc
CC_FLAGS = -std=c9x -g -O0

build: $(EXEC) $(TEST)

$(EXEC):%:%.c $(HEADERS)
	$(CC) $(CC_FLAGS) $(firstword $+) -o $@

test: $(TEST)
	valgrind --leak-check=full ./$(TEST)

$(TEST):%:%.c $(HEADERS)
	$(CC) $(CC_FLAGS) $(firstword $+) -o $@

clean:
	rm -f $(EXEC) $(TEST)

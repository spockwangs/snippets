# Makefile
#

CC = gcc 
CFLAGS = -g -std=c99 -pedantic -W -Wall
EXECS = missing1 gen missing2 rotate sign squash

all: $(EXECS)

gen: generate.c 
	$(CC) $(CFLAGS) -o $@ $^

clean:
	-$(RM) *.o *.out core* $(EXECS)

.PHONY: all clean

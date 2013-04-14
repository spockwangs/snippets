# Makefile
#

CC = gcc 
CFLAGS = -g -std=c99 -pedantic -W -Wall

all: sort gen

sort: sort.c bit.c 

gen: generate.c bit.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	-$(RM) *.o *.out core* sort gen

.PHONY: all clean

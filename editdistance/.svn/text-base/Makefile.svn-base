# -*- makefile -*-

CC = gcc
CFLAGS = -g -W -Wall -std=c99 -pedantic

all: editdist editdist2

editdist: editdistance.c
	$(CC) $(CFLAGS) -o $@ $^

editdist2: editdistance2.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) *.o *~ a.out editdist editdist2

.PHONY: all clean
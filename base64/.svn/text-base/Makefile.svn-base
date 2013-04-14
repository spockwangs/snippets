# -*- Makefile -*-

CC = gcc
CFLAGS = -g -W -Wall -O2 -std=c99 -pedantic
PROGRAMS = encode decode genbytes

all: $(PROGRAMS)

test: retest.sh $(PROGRAMS)
	./retest.sh

clean:
	$(RM) *~ \#*\# a.out core $(PROGRAMS)

.PHONY: all clean

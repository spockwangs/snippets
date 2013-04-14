# Makefile for ed.

CC = gcc
CFLAGS = -g -std=c99 -pedantic -W -Wall

all: ed

ed: buf.o clines.o pat.o

clean:
	$(RM) -f *.o *~ a.out

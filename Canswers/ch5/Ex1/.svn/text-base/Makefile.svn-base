# Makefile for ex1.c
#

CC = gcc
CFLAGS = -ansi -pedantic -W -Wall -Wconversion
RM = rm -rf

EXEC = ex1
SRCFILES = $(wildcard *.c)
OBJFILES = $(patsubst %.c, %.o, $(SRCFILES))

all: $(EXEC)

$(EXEC): $(OBJFILES)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJFILES) $(EXEC)

.PHONY: all clean

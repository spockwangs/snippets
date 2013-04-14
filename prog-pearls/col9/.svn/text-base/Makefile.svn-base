# Makefile
#

CC = gcc 
CFLAGS = -g -std=c99 -pedantic -W -Wall
CXX = g++
CXXFLAGS = -g -std=c++98 -pedantic -W -Wall
EXECS = genbins macfun prob4 prob7 prob9 prob12

all: $(EXECS)

genbins: genbins.c
	$(CC) -pg $(CFLAGS) -o $@ $^

clean:
	-$(RM) *.o *.out core* $(EXECS)

.PHONY: all clean

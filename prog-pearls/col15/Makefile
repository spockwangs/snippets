# Makefile
#

CC = gcc 
CFLAGS = -g -std=c99 -pedantic -W -Wall
CXX = g++
CXXFLAGS = -g -std=c++98 -pedantic -W -Wall
EXECS = longdup markov markovhash markovlet wordfreq1 wordfreq2 wordlist \
	prob5 prob8 prob9 prob6 prob10

all: $(EXECS)

wordfreq1: wordfreq.c
	$(CC) $(CFLAGS) -o $@ $^

wordfreq2: wordfreq.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	-$(RM) *.o *.out core* $(EXECS)

.PHONY: all clean

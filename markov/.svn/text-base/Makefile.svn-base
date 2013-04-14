
CC = gcc 
CXX = g++
CFLAGS = -g -std=c99 -pedantic -W -Wall
CXXFLAGS = -g -W -Wall -std=c++98 -pedantic

all: markov markovcpp

markov: markov.c

markovcpp: markov.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	-@$(RM) markov markovcpp core* *.o *~

.PHONY: all clean

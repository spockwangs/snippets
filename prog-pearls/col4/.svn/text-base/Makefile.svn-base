# Makefile
#

CC = gcc 
CFLAGS = -g -std=c99 -pedantic -W -Wall
CXX = g++
CPPFLAGS = -g -std=c++98 -pedantic -W -Wall

all: prob2 prob11

# rules
%.o: %.cpp
	$(CXX) $(CPPFLAGS) -c $@ $^

clean:
	-$(RM) *.o *.out core* prob2 prob11

.PHONY: all clean

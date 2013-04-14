# Makefile
#

CC = gcc 
CFLAGS = -g -std=c99 -pedantic -W -Wall
CXX = g++
CPPFLAGS = -g -std=c++98 -pedantic -W -Wall

all: binary_search

# rules
%.o: %.cpp
	$(CXX) $(CPPFLAGS) -c $@ $^

clean:
	-$(RM) *.o *.out core* binary_search

.PHONY: all clean

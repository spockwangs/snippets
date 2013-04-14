# Makefile

CC = gcc
CFLAGS = -g -pg -std=c99 -pedantic -W -Wall -Wconversion
CXX = g++
CXXFLAGS = -g -std=c99 -pedantic -W -Wall
OBJS = $(patsubst %.c,%.o,$(wildcard *.c))

../libalgo.a: $(OBJS)
	@echo Generating $@ ...
	@$(AR) ur $@ $^

clean:
	@echo Cleanning ...
	@$(RM) *~ *.o core* a.out

%.o: %.c
	@echo Compiling $^ ...
	@$(CC) $(CFLAGS) -c -o $@ $^

%.o: %.cpp
	@echo Compiling $^ ...
	@$(CXX) $(CXXFLAGS) -c -o $@ $^

.PHONY: clean



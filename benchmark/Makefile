# Makefile for md5
#

CC = g++ -g -std=c++11 -pedantic -W -Wall

all: benchmark

benchmark: main.cpp benchmark.cpp benchmark.h
	$(CC) -o $@ benchmark.cpp main.cpp

clean:
	@echo Cleanning ... 
	@$(RM) *.out *.o *~ benchmark

.PHONY: all clean

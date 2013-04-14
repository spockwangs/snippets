# Makefile for md5
#

CC = gcc -g -std=c99 -pedantic -W -Wall

all: md5sum

md5sum: md5.h md5.c main.c
	$(CC) -o $@ md5.c main.c

clean:
	@echo Cleanning ... 
	@$(RM) *.out *.o *~ md5sum

.PHONY: all clean


############## Beginning of Makefile #################


CC = gcc
CFLAGS = -ansi -pedantic -W -Wall
RM = rm -rf
SOURCES = $(wildcard, *.c)
OBJS = $(patsubst %.c, %.o, $(SOURCES))


all: ex7

clean:
	$(RM) *.o $(patsubst %.c, %, $(wildcard *.c))

.PHONY: all clean

############# End of Makefile #######################

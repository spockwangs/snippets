
############## Beginning of Makefile #################


CC = gcc
CFLAGS = -ansi -pedantic -W -Wall
RM = rm -rf
SOURCES = $(wildcard, *.c)
OBJS = $(patsubst %.c, %.o, $(SOURCES))
EXECS = ex8


all: $(EXECS)

clean:
	$(RM) *.o $(EXECS)

.PHONY: all clean

############# End of Makefile #######################

# Makefile for dc

CXX = g++
CPPFLAGS = -ansi -W -Wall -g

OBJ_FILES = main.o driver.o lexer.o parser.o

all: dc dc2

dc: $(OBJ_FILES)
	$(CXX) $(CPPFLAGS) -o $@ $^

dc2: dc2.cpp

parser.o: parser_impl.h

driver.o: error.h parser.h lexer.h

%.o: %.h

clean: 
	$(RM) dc dc2 $(OBJ_FILES) core* a.out *~

.PHONY: all clean

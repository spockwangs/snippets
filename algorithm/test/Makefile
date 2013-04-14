# Makefile

CC = gcc
CFLAGS = -g -pg -std=c99 -pedantic -W -Wall
CXX = g++
CPPFLAGS = 
PROGRAMS = $(patsubst %.c, %, $(wildcard test_*.c))

all: $(PROGRAMS)

test_quicksort: test_quicksort.c ../inc/sort.h ../libalgo.a

test_heapsort: test_heapsort.c ../inc/sort.h ../libalgo.a

test_insertsort: ../inc/sort.h ../libalgo.a

test_binsearch: ../inc/binsearch.h ../libalgo.a

test_countsort: ../inc/sort.h ../libalgo.a

test_bucketsort: ../inc/sort.h ../libalgo.a

test_unimodalsearch: ../inc/algorithm.h ../libalgo.a

test_select: ../inc/algorithm.h ../libalgo.a

test_bst: ../inc/bst.h ../src/bst.o

test_rbtree: ../inc/bst.h ../src/RBtree.o

test_intersearch: ../libalgo.a

test_skiplist: ../libalgo.a

test_trie: ../libalgo.a

test_pat: ../libalgo.a

test_st: ../libalgo.a

test_suffix: ../libalgo.a

test: $(PROGRAMS)
	@for each in $(PROGRAMS); do \
	    echo Running "$$each" ...; \
	    ./"$$each"; \
	    echo; \
	done

clean:
	@echo Cleaning ...
	-@$(RM) *.o core* *~ a.out $(PROGRAMS)

.PHONY: clean all

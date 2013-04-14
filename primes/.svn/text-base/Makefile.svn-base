
CC = gcc
CFLAGS = -g -W -Wall -pedantic -std=c99

all: primes1 primes2 primes3

primes1: primes_multiprocess.c
	$(CC) $(CFLAGS) -o $@ $^

primes2: primes_multithread.c
	$(CC) $(CFLAGS) -o $@ $^ -lpthread

primes3: printprimes.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) primes1 primes2 primes3 *.o *~ a.out

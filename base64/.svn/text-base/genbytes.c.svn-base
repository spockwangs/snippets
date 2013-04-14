/*
 * genbytes.c -- generate random byte to stdout
 *
 * Time-stamp: <2010-08-06 20:00:42 wbb>
 *
 * Usage: ./genbytes #bytes >outputfile
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <error.h>

int main(int argc, char *argv[])
{
     unsigned int seed = time(0);
     srand(seed);
     
     if (argc != 2) {
          error(1, 0, "Usage: genbytes #bytes");
     }
     
     int nbytes = atoi(argv[1]);
     if (nbytes <= 0) {
          error(1, 0, "Positive number required!");
     }

     int i;
     for (i = 0; i < nbytes; i++)
          putchar((char) rand());
}

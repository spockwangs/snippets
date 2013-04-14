/*
 * primes.c -- Print all primes, multiprocessing version.
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>

const int debug = 1;

void forkchild(int []);

int main(void)
{
    int fds[2], i;

    if (pipe(fds) < 0) {
        perror("pipe");
        exit(1);
    }
    forkchild(fds);
    close(fds[0]);
    for (i = 2; ; i++) {
        write(fds[1], &i, sizeof i);
    }
    return 0;
}


/* forkchild: fork a right neighbour to filter numbers */
void forkchild(int fds[])
{
    pid_t child;

    if ((child = fork()) < 0) {
        perror("fork");
        exit(1);
    } else if (child == 0) {
        int filedes[2], p, i;

        close(fds[1]);
        if (pipe(filedes) < 0) {
            perror("pipe");
            exit(1);
        }
        forkchild(filedes);
        close(filedes[0]);

        /* read a prime from left neighbour and print it */
        read(fds[0], &p, sizeof p);
        printf("%d ", p);
        fflush(stdout);
        while (1) {
            /* read numbers from left neighbour */
            read(fds[0], &i, sizeof i);
            /* if not divisable by prime 'p' write it to right
             * neighbour 
             */
            if (i % p)
                write(filedes[1], &i, sizeof i);
        }
        exit(0);
    }
}


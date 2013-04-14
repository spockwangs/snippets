/* 
 * primes -- Print all primes (in principle), multithreading version.
 */

#include <stdio.h>
#include <string.h>
#include <error.h>
#include <errno.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *primes(void *arg);

int main(void)
{
    int         fd[2], err;
    pthread_t   tid;

    if (pipe(fd) < 0)
        error(1, errno, "pipe error");

    setbuf(stdout, NULL);
    if ((err = pthread_create(&tid, NULL, primes, (void *) fd[0])) != 0) {
        fprintf(stderr, "pthread_create error: %s\n", strerror(err));
        exit(1);
    }

    for (int i = 2; ; i++) {
        if (write(fd[1], &i, sizeof i) < 0)
            error(1, errno, "write error");
    }

    return 0;
}

void *primes(void *arg)
{
    int         i, p, fd, fd2[2], err;
    pthread_t   tid;

    fd = (int) arg;
    if (read(fd, &p, sizeof p) < 0)
        error(1, errno, "read error");
    printf("%d ", p);

    if (pipe(fd2) < 0) {
        error(1, errno, "pipe error");
    }

    if ((err = pthread_create(&tid, NULL, primes, (void *) fd2[0])) != 0) {
        fprintf(stderr, "pthread_create error: %s\n", strerror(err));
        exit(1);
    }

    while (1) {
        if (read(fd, &i, sizeof i) < 0)
            error(1, errno, "read error");
        if (i % p)
            if (write(fd2[1], &i, sizeof i) < 0)
                error(1, errno, "write error");
    }
}

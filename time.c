/*
 * time.c -- print real time, user time and sys time for a process, like time(1)
 *
 * Compile
 *   gcc -g -W -Wall -std=c99 -pedantic time.c
 */

#include <stdio.h>
#include <errno.h>
#include <error.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/times.h>

#undef MAXLINE

#define MAXLINE 1024

static void pr_times(clock_t real, struct tms *tmsstart, struct tms *tmsend);

int main(int argc, char *argv[])
{
    char        buf[MAXLINE];
    struct tms  tmsstart, tmsend;
    clock_t     start, end;

    strcpy(buf, " ");
    for (int i = 1; i < argc; i++)
        sprintf(buf, "%s%s ", buf, argv[i]);

    if ((start = times(&tmsstart)) == -1)
        error(1, errno, "times error");

    if (system(buf) < 0)
        error(1, errno, "system error");

    if ((end = times(&tmsend)) == -1)
        error(1, errno, "times error");

    pr_times(end-start, &tmsstart, &tmsend);
    return 0;
}

static void pr_times(clock_t real, struct tms *tmsstart, struct tms *tmsend)
{
    static long clktck = 0;

    if (clktck == 0)    /* first through */
        if ((clktck = sysconf(_SC_CLK_TCK)) < 0)
            error(1, errno, "sysconf error");
    printf("\nreal\t%7.3fs\n", real / (double) clktck);
    printf("user\t%7.3fs\n",
            (tmsend->tms_cutime - tmsstart->tms_cutime) / (double) clktck);
    printf("sys\t%7.3fs\n",
            (tmsend->tms_cstime - tmsstart->tms_cstime) / (double) clktck);
}

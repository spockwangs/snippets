/*
 * red_string.c -- Show how to print red string to terminal.
 * 
 * This program will print a red string "Hello" using ANSI Escape
 * Sequence `\e[31m' to turn on red attribute and `\e[0m' to undo the
 * effect. The former sequence is printed by the parent process and
 * the string is printed by child process. The result shows that the
 * Ansi escape sequence must be processed by console device drivers,
 * not system calls.
 *
 * Compile
 *   gcc -W -Wall -std=c99 -pedantic red_string.c
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
    pid_t pid;

    printf("\e[31m");
    if ((pid = fork()) == 0) {
        printf("Hello");
        return 0;
    }

    /* wait for child to quit */
    wait(0);
    printf("\e[0m\n");

    return 0;
}

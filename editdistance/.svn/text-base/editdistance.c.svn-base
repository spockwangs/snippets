/*
 * editdistance.c -- compute edit distance of 2 strings
 */

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <limits.h>
#include <assert.h>

#define RIGHT_COST      0
#define REPLACE_COST    4
#define INSERT_COST     3
#define DELETE_COST     2

enum { RIGHT, LEFT, INSERT, DELETE, REPLACE };

void PrintOps(int *ops, char x[], int m, char y[], int n, int i, int j, int *cost);

void printEditDist(char x[], char y[])
{
    int m, n;
    int * cost, *ops;
    int cost_for_right_or_replace;
    int cost_for_insert;
    int cost_for_delete;
    int min;
    int i, j;
    int opDone;

    m = strlen(x);
    n = strlen(y);
    cost = (int *) malloc((m+1) * (n+1) * sizeof(int));
    assert(cost != NULL);
    ops = (int *) malloc((m+1) * (n+1) * sizeof(int));
    assert(ops != NULL);
    for (i = 0; i <= m; i++) {
        for (j = 0; j <= n; j++) {
            cost_for_right_or_replace = cost_for_delete = cost_for_insert = INT_MAX;
            if (i > 0 && j > 0) {
                if (x[i-1] == y[j-1])
                    cost_for_right_or_replace = cost[(i-1)*(n+1)+j-1] + RIGHT_COST;
                else {
                    cost_for_right_or_replace = cost[(i-1)*(n+1)+j-1] + REPLACE_COST;
                }
            }
            if (i > 0) {
                cost_for_delete = cost[(i-1)*(n+1)+j] + DELETE_COST;
            }
            if (j > 0) {
                cost_for_insert = cost[i*(n+1)+j-1] + INSERT_COST;
            }
            min = cost_for_right_or_replace;
            if (x[i-1] == y[j-1])
                opDone = RIGHT;
            else
                opDone = REPLACE;
            if (min > cost_for_delete) {
                min = cost_for_delete;
                opDone = DELETE;
            }
            if (min > cost_for_insert) {
                min = cost_for_insert;
                opDone = INSERT;
            }
            if (i == 0 && j == 0)
                min = 0;
            cost[i*(n+1)+j] = min;
            ops[i*(n+1)+j] = opDone;
        }
    }
    printf("x: %s\n", x);
    printf("y: %s\n", y);
    printf("Edit Distance: %d\n", cost[m*(n+1)+n]);
    printf("\n");
    PrintOps(ops, x, m, y, n, m, n, cost);
    free(ops);
    free(cost);
}

/* PrintOps: print operations performed on string x. The first call is
 * PrintOps(ops, x, m, y, n, m, n, cost)
 */
void PrintOps(int *ops, char x[], int m, char y[], int n, int i, int j, int *cost)
{
    int k;

    assert(ops != NULL && cost != NULL);
    if (i >= 1 || j >= 1)
        switch (ops[i*(n+1)+j]) {
            case RIGHT:
                PrintOps(ops, x, m, y, n, i-1, j-1, cost);
                printf("%-8s| %d | %3d | ", 
                        "Right", 0, cost[i*(n+1)+j]);
                break;
            case INSERT:
                PrintOps(ops, x, m, y, n, i, j-1, cost);
                printf("%-8s| %d | %3d | ",
                       "Insert", 3, cost[i*(n+1)+j]);
                break;
            case REPLACE:
                PrintOps(ops, x, m, y, n, i-1, j-1, cost);
                printf("%-8s| %d | %3d | ",
                       "Replace", 4, cost[i*(n+1)+j]);
                break;
            case DELETE:
                PrintOps(ops, x, m, y, n, i-1, j, cost);
                printf("%-8s| %d | %3d | ",
                       "Delete", 2, cost[i*(n+1)+j]);
                break;
        }
    else {
        printf("%-8s| c |Total| z\n", "Oper");
        printf("----------------------------------\n");
        printf("%-8s| %d | %3d | ",
               "Initial", 0, 0);
    }
    for (k = 0; k < j; k++)
        printf("%c", y[k]);
    printf("*");
    for (k = i; k < m; k++)
        printf("%c", x[k]);
    printf("\n");
}

int main(int argc, char **argv)
{
    if (argc != 3) {
        printf("Usage: %s string1 string2\n", argv[0]);
        return 1;
    }
    printEditDist(argv[1], argv[2]);
    return 0;
}


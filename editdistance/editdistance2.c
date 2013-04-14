/*
 * editdistance2.c -- compute edit distance of 2 strings, using a minor different algorithm
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

void PrintOps(int *ops, const char x[], const char y[]);

void printEditDist(const char x[], const char y[])
{
    int m, n;
    int * cost, *ops;
    int cost_for_delete, cost_for_insert, cost_for_replace;
    int i, j;

    m = strlen(x);
    n = strlen(y);
    cost = (int *) malloc((m+1) * (n+1) * sizeof(int));
    assert(cost != NULL);
    ops = (int *) malloc((m+1)*(n+1)*sizeof(int));
    assert(ops != NULL);

    cost[m*(n+1)+n] = 0;
    for (i = m, j = n-1; j >= 0; j--) {
        ops[i*(n+1)+j] = INSERT;
        cost[i*(n+1)+j] = cost[i*(n+1)+j+1] + INSERT_COST;
    }
    for (j = n, i = m-1; i >= 0; i--) {
        cost[i*(n+1)+j] = cost[(i+1)*(n+1)+j] + DELETE_COST;
        ops[i*(n+1)+j] = DELETE;
    }

    for (i = m-1; i >= 0; i--) {
        for (j = n-1; j >= 0; j--) {
            if (x[i] == y[j]) {
                cost[i*(n+1)+j] = cost[(i+1)*(n+1)+j+1] + RIGHT_COST;
                ops[i*(n+1)+j] = RIGHT;
            } else {
                cost_for_delete = cost[(i+1)*(n+1)+j] + DELETE_COST;
                cost_for_insert = cost[i*(n+1)+j+1] + INSERT_COST;
                cost_for_replace = cost[(i+1)*(n+1)+j+1] + REPLACE_COST;
                if (cost_for_delete < cost_for_insert) {
                    if (cost_for_delete < cost_for_replace) {
                        cost[i*(n+1)+j] = cost_for_delete;
                        ops[i*(n+1)+j] = DELETE;
                    } else {
                        cost[i*(n+1)+j] = cost_for_replace;
                        ops[i*(n+1)+j] = REPLACE;
                    }
                } else {
                    if (cost_for_insert < cost_for_replace) {
                        cost[i*(n+1)+j] = cost_for_insert;
                        ops[i*(n+1)+j] = INSERT;
                    } else {
                        cost[i*(n+1)+j] = cost_for_replace;
                        ops[i*(n+1)+j] = REPLACE;
                    }
                }
            }
        }
    }
    printf("x: %s\n", x);
    printf("y: %s\n", y);
    printf("Edit Distance: %d\n", cost[0]);
    printf("\n");
    PrintOps(ops, x, y);
    free(ops);
    free(cost);
}

void PrintOps(int *ops, const char x[], const char y[])
{
    int i, j, k, m, n;
    int costSofar;

    n = strlen(y);
    m = strlen(x);
    printf("%-8s| c |Total| z\n", "Oper");
    printf("------------------------------------------------\n");
    printf("%-8s| %d | %3d | ", "Initial", 0, 0);
    printf("*%s\n", x);
    i = j = 0;
    costSofar = 0;
    while (i < m || j < n) {
        switch (ops[i*(n+1)+j]) {
            case RIGHT:
                costSofar += RIGHT_COST;
                printf("%-8s| %d | %3d | ", 
                        "Right", RIGHT_COST, costSofar);
                i++;
                j++;
                break;
            case INSERT:
                costSofar += INSERT_COST;
                printf("%-8s| %d | %3d | ",
                       "Insert", INSERT_COST, costSofar);
                j++;
                break;
            case REPLACE:
                costSofar += REPLACE_COST;
                printf("%-8s| %d | %3d | ",
                       "Replace", REPLACE_COST, costSofar);
                i++;
                j++;
                break;
            case DELETE:
                costSofar += DELETE_COST;
                printf("%-8s| %d | %3d | ",
                       "Delete", DELETE_COST, costSofar);
                i++;
                break;
        }
        for (k = 0; k < j; k++)
            printf("%c", y[k]);
        printf("*");
        for (k = i; k < m; k++)
            printf("%c", x[k]);
        printf("\n");
    }
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


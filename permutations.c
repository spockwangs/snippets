/*****************************************************************************
 * Write a program to print all permutations of n numbers ranging from 1 to n.
 *
 * Author: wbb
 * Date: 2009-05-18
 *
 * COMPILE
 *   gcc -g -W -Wall -pedantic -std=c99 permutations.c
 */

#include <stdio.h>
#include <assert.h>
#include <malloc.h>

/* function declarations */
void swap(int *p1, int *p2);
void recur_perm(int list[], int k, int m);
void permute_recur(int n);

/****************************************************************************
 * permute - Iterative version.  
 *      print all permutations from 1 to n.  */
void permute_iterate(int n)
{
    int i, k;
    int *pavail;     /* indicate if a number i is available */
    int *permutation;   /* the permutation */
    
    pavail = (int *) malloc(n * sizeof(int));
    assert(pavail != NULL);
    permutation = (int *) malloc(n * sizeof(int));
    assert(permutation != NULL);
    
    /* initialize pavail; all numbers are available */
    for (i = 0; i < n; i++) {
        pavail[i] = 1;
    }

    /* fill the permutation */
    i = 0;
    while (1) {
        k = 1;
        while (k <= n) {   
            if (pavail[k-1]){   /* Is k available? */
                permutation[i++] = k;
                pavail[k-1] = 0;    /* indicate k is occupied */
            }
            k++;
        }
        /* print a permutation */
        for (i = 0; i < n; i++)
            printf("%d%s", permutation[i], i == n-1 ? "\n" : ", ");
        i = n - 1;
        do {    /* trace back */
            /* indicate (i+1)th number in permutation is available */
            pavail[permutation[i]-1] = 1;   
            i--;
            if (i < 0)      /* all permutations have been printed */
                break;
            /* find next larger available number for index i in permutation */
            for (k = permutation[i]+1; k <= n && (pavail[k-1] == 0); k++)
                ;
            if (k <= n)     /* if we find it break out */
                break;
        } while (1);
        if (i < 0)      /* all permutations have been printed */
            break;
        pavail[permutation[i]-1] = 1;
        permutation[i] = k;
        pavail[k-1] = 0;
        i++;
    }

    free(pavail);
    free(permutation);
}

void swap(int *p1, int *p2)
{
    int t;

    t = *p1;
    *p1 = *p2;
    *p2 = t;
}

/*****************************************************************************
 * permute_recur - recursive version
 *      Print all permutations of n numbers.
 */
void permute_recur(int n)
{
    int *list;
    int i;

    assert(n > 0);
    list = (int *) malloc(n * sizeof(int));
    assert(list != NULL);
    
    /* initialize the list */
    for (i = 0; i < n; i++)
        list[i] = i+1;
    recur_perm(list, 0, n);
    free(list);
}

void recur_perm(int list[], int k, int m) 
{     
    int i;     

    if (k >= m) {          
        for (i = 0; i < m; i++)             
            printf("%d ", list[i]);         
        printf("\n");         
    } else {         
        for (i = k; i < m; i++) {             
            swap(&list[k], &list[i]);             
            recur_perm(list, k + 1, m);             
            swap(&list[k], &list[i]);         
        }
    } 
} 


int main()
{
    int n;

    printf("Permutations from 1 to ");
    scanf("%d", &n);
    printf("Iterative version: \n");
    permute_iterate(n);
    printf("\nRecursive version: \n");
    permute_recur(n);

    return 0;
}

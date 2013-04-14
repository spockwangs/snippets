/*
 * prob7.c -- Problem 7 of column 9
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>


int bits(unsigned char byte)
{
    int count = 0;
    while (byte) {
        ++count;
        byte &= byte-1;
    }
    return count;
}


int countbits(const unsigned char *p, int n)
{
    static int ones[256], isinit;

    if (!isinit) {
        for (int i = 0; i < 256; i++)
            ones[i] = bits((unsigned char) i);
        isinit = 1;
    }

    if (p == NULL)
        return 0;
    
    int count = 0;
    for (int i = 0; i < n; i++) {
        count += ones[*p++];
    }
    return count;
}


int countbits2(const unsigned char *p, int n)
{
    int count = 0;
    for (int i = 0; i < n; i++)
        count += bits(*p++);
    return count;
}


#define MAXN 100000000

unsigned char x[MAXN];

int main()
{
    srand(time(NULL));
    for (int i = 0; i < MAXN; i++)
        x[i] = (unsigned char) (rand() % 256);

    int algnum, n;
    while (scanf("%d %d", &algnum, &n) != EOF) {
        if (n > MAXN) {
            printf("n should be no more than %d\n", MAXN);
            continue;
        }

        clock_t start, ticks;
        int thisans, chkans;
        start = clock();
        switch (algnum) {
        case 1:
            thisans = countbits(x, n);
            break;
        case 2:
            thisans = countbits2(x, n);
            break;
        default:
            break;
        }
        ticks = clock() - start;
        printf("alg: %d, n: %d, ticks: %d, sec: %.2f\n",
                algnum, n, (int) ticks, (float) ticks / CLOCKS_PER_SEC);
        chkans = countbits2(x, n);
        if (thisans != chkans)
            printf("error: mismatch with countbits2(): %d\n", chkans);
    }

    return 0;
}


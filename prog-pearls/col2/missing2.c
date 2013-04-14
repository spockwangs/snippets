/*
 * missing2.c -- Solution 2 to Problem A of Column 2
 *   Find one missing integer in a file containing at most four
 *   billion 32-bit integergs in random order.
 *
 *   Use binary search to find one missing integer.
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <errno.h>
#include <error.h>
#include <assert.h>

#define BITS    16

int main(void)
{
    uint32_t find_missing(FILE *fp, uint32_t lo, uint32_t hi);

    printf("%u\n", find_missing(stdin, 0, (1<<BITS)-1));
    return 0;
}


uint32_t find_missing(FILE *fp, uint32_t lo, uint32_t hi)
{
    uint32_t mid, n, c_lo, c_hi;
    FILE *fp_lo, *fp_hi;
    char filename[100];
    int i = 0, e;

    while (lo < hi) {
        sprintf(filename, "/tmp/%04d.txt", i++);
        fp_lo = fopen(filename, "w+");
        assert(fp_lo != NULL);
        sprintf(filename, "/tmp/%04d.txt", i++);
        fp_hi = fopen(filename, "w+");
        assert(fp_hi != NULL);

        c_lo = c_hi = 0;
        mid = lo + (hi-lo)/2;
        e = 0;

        while (fscanf(fp, "%u", &n) != EOF) {
            if (n < mid) {
                fprintf(fp_lo, "%u\n", n);
                c_lo++;
            } else if (n > mid) {
                fprintf(fp_hi, "%u\n", n);
                c_hi++;
            } else
                e = 1;
        }
        if (ferror(fp))
            error(EXIT_FAILURE, errno, "error reading input file");

        fclose(fp);
        if (e == 0) {
            fclose(fp_lo);
            fclose(fp_hi);
            return mid;
        }
        if (c_lo == 0) {
            fclose(fp_lo);
            fclose(fp_hi);
            return lo;
        }
        if (c_hi == 0) {
            fclose(fp_lo);
            fclose(fp_hi);
            return hi;
        }
        if (c_lo < c_hi) {
            fclose(fp_hi);
            fp = fp_lo;
            hi = mid-1;
        } else {
            fclose(fp_lo);
            fp = fp_hi;
            lo = mid+1;
        }
        fseek(fp, 0, SEEK_SET);
    }
    
    return lo;
}



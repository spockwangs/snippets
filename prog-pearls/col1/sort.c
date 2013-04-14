/*
 * sort.c - Programming Pearls, Column 1
 *   Sort a file containing less than 10^7 records, without
 *   duplicates.  Each record is a nonnegative integer less than 10^7.
 *
 * Usage: sort -c N input_file outptu_file
 *   -c N           N is the maximum of records.
 *   input_file     file containing records which need to be sorted
 *   output_file    to store sorted output
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>     /* for getopt() */
#include <error.h>
#include <errno.h>
#include "bit.h"        /* for bit vector data structure */


static void usage(void)
{
    fprintf(stderr, "Usage: sort -c N input_file output_file\n");
    exit(EXIT_FAILURE);
}


int main(int argc, char *argv[])
{
    int n = -1, c;
    extern int opterr, optind;
    extern char *optarg;

    opterr = 0;
    while ((c = getopt(argc, argv, ":c:")) != -1) {
        switch (c) {
        case 'c':
            n = atoi(optarg);
            break;
        default:
            usage();
            break;
        }
    }
    if (n == -1 || argc-optind != 2)
        usage();
    argv += optind;

    FILE *fin, *fout;
    fin = fopen(argv[0], "rb");
    if (fin == NULL)
        error(EXIT_FAILURE, errno, "can not open '%s'", argv[0]);
    fout = fopen(argv[1], "w");
    if (fout == NULL)
        error(EXIT_FAILURE, errno, "can not open '%s'", argv[1]);


    /*
     * Read records from input file.
     * We need to do sanity check: no duplicate records; each record
     * is in [0, n); all records should be integers.
     */

    Bit_T bv = Bit_new(n);
    int num;
    while (fscanf(fin, "%d", &num) != EOF) {
        if (num < 0 || num >= n)
            error(EXIT_FAILURE, 0, "error: the record '%d' in '%s' is not in the range [0, %d)",
                    num, argv[0], n);
        if (Bit_get(bv, num))
            error(EXIT_FAILURE, 0, "error: duplicate record '%d' in '%s'\n",
                    num, argv[0]);
        Bit_put(bv, num, 1);
    }
    if (ferror(fin))
        error(EXIT_FAILURE, errno, "error reading '%s'", argv[0]);
    fclose(fin);

    /*
     * Sort records and output sorted records into the output file.
     */
    
    int i;
    for (i = 0; i < n; i++) {
        if (Bit_get(bv, i))
            if (fprintf(fout, "%d\n", i) < 0)
                error(EXIT_FAILURE, errno, "error writing '%s'", argv[1]);
    }
    Bit_free(&bv);
    fclose(fout);

    return 0;
}


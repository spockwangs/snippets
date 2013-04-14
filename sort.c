/*
 * sort -- Merge sort big files.  See Chapter 4 of "Software Tools".
 *
 * who: wbbtiger@gmail.com
 * when: 2010-10-29
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXTEXT 1000000
#define NAMESIZE 50
#define MERGEORDER 10
#define MAXPTR 10000
#define MAXLINE 1000
#define N 2                     /* balanced N-way merge */

int gtext(char *lineptr[], int maxlines, char linebuf[], int maxtext, int *nlines, FILE *in);
FILE *makefile(int n);
void gname(int n, char name[], size_t size);
void gopen(FILE *infile[], int low, int lim);
void gremove(FILE *infile[], int low, int lim);
void merge(FILE *infile[], int nfiles, FILE *outfile);
void reheap(char *lineptr[], int nf, char linebuf[]);
void ptext(char *lineptr[], int nlines, FILE *out);
int min(int a, int b);
void fcopy(FILE *src, FILE *dest);
int qcmpstr(const void *pl, const void *pr);
void swap(int *p, int *q);

int main()
{
     char linebuf[MAXTEXT], name[NAMESIZE];
     FILE *infile[MERGEORDER];
     FILE *outfile;
     char *lineptr[MAXPTR];
     int nlines, t, outlow, outhigh, mergelow, mergehigh;

     outlow = 1;
     mergelow = outlow + N;
     mergehigh = mergelow-1;
     for (;;) {
          /*
           * Read chunks from stdin and write to files outlow...outhigh.
           */
          for (outhigh = outlow; outhigh < outlow+N; outhigh++) {
               t = gtext(lineptr, MAXPTR, linebuf, MAXTEXT, &nlines, stdin);
               qsort(lineptr, nlines, sizeof(lineptr[0]), qcmpstr);
               outfile = makefile(outhigh);
               ptext(lineptr, nlines, outfile);
               fclose(outfile);
               if (t == EOF)
                    break;
          }
          if (outhigh >= outlow+N)
               outhigh--;

          /*
           * Merge files outlow...outhigh to mergehigh.
           */
          gopen(infile, outlow, outhigh);
          ++mergehigh;
          outfile = makefile(mergehigh);
          merge(infile, outhigh-outlow+1, outfile);
          fclose(outfile);

          /*
           * If the merge group is full, merge them to outlow and exchange
           * merge group and sorting group.
           */
          if (mergehigh-mergelow+1 >= N) {
               gopen(infile, mergelow, mergehigh);
               outfile = makefile(outlow);
               merge(infile, mergehigh-mergelow+1, outfile);
               fclose(outfile);
               swap(&outlow, &mergelow);
               mergehigh = mergelow;
          }
          if (t == EOF)
               break;
     }

     gopen(infile, mergelow, mergehigh);
     merge(infile, mergehigh-mergelow+1, stdout);
     gopen(infile, 1, 2*N);
     gremove(infile, 1, 2*N);
     return 0;
}

void swap(int *p, int *q)
{
     int t = *p;
     *p = *q;
     *q = t;
}

/*
 * qcmpstr --
 *   Compare two strings.  Interface to qsort().
 */
int qcmpstr(const void *pl, const void *pr)
{
     const char *s1 = *(const char **) pl;
     const char *s2 = *(const char **) pr;
     return strcmp(s1, s2);
}

/*
 * gtext --
 *   Read lines from 'in' which are stored in 'linebuf[]' and pointers to
 *   each line are stored in 'lineptr[]'.
 */
int gtext(char *lineptr[], int maxlines, char linebuf[], int maxtext, int *nlines, FILE *in)
{
     int lbp = 0;
     char *s;

     *nlines = 0;
     while (lbp < maxtext-MAXLINE && *nlines < maxlines) {
          s = fgets(&linebuf[lbp], MAXLINE, in);
          if (s == NULL)
               return EOF;
          lineptr[(*nlines)++] = &linebuf[lbp];
          lbp += strlen(s)+1;
     }
     return 1;
}

/*
 * ptext --
 *   Write lines in 'lineptr[]' to 'out'.
 */
void ptext(char *lineptr[], int nlines, FILE *out)
{
     int i;

     for (i = 0; i < nlines; i++)
          fputs(lineptr[i], out);
}

int min(int a, int b)
{
     return a < b ? a : b;
}

/*
 * fcopy --
 *   Copy file from 'src' to 'dest'.
 */
void fcopy(FILE *src, FILE *dest)
{
     char buf[MAXLINE];
     while (fgets(buf, MAXLINE, src) != NULL)
          fputs(buf, dest);
}

/*
 * makefile --
 *   Make a unique file from an integer 'n'.
 */
FILE *makefile(int n)
{
     char name[NAMESIZE];
     FILE *fp;
     
     gname(n, name, NAMESIZE);
     fp = fopen(name, "w+");
     if (fp == NULL)
          perror(name);
     return fp;
}

/*
 * gname --
 *   Make a unique name from an integer 'n'.
 */
void gname(int n, char name[], size_t size)
{
     snprintf(name, size, "stemp%d", n);
}

/*
 * gopen --
 *   Open a group of files low...lim.
 */
void gopen(FILE *infile[], int low, int lim)
{
     char name[NAMESIZE];
     int i;

     for (i = 0; i < lim-low+1; i++) {
          gname(low+i, name, NAMESIZE);
          infile[i] = fopen(name, "r");
     }
}

/*
 * gremove --
 *   Remove a group of files low...lim.
 */
void gremove(FILE *infile[], int low, int lim)
{
     char name[NAMESIZE];
     int i;

     for (i = 0; i < lim-low+1; i++) {
          if (infile[i] != NULL)
               fclose(infile[i]);
          gname(low+i, name, NAMESIZE);
          remove(name);
     }
}

#define MERGETEXT 20000

/*
 * merge --
 *   Merge sort a group of files to 'outfile'.
 */
void merge(FILE *infile[], int nfiles, FILE *outfile)
{
     char *lineptr[MERGEORDER];
     char linebuf[MERGETEXT];
     int lbp = 0, nf = 0;
     int i, inf;
     
     for (i = 0; i < nfiles; i++) {
          if (fgets(&linebuf[lbp], MAXLINE, infile[i]) != NULL) {
               lineptr[nf++] = &linebuf[lbp];
               lbp += MAXLINE;
          }
     }
     qsort(lineptr, nf, sizeof(lineptr[0]), qcmpstr);
     while (nf > 0) {
          fputs(lineptr[0], outfile);
          inf = (lineptr[0] - linebuf) / MAXLINE;
          if (fgets(lineptr[0], MAXLINE, infile[inf]) == NULL) {
               lineptr[0] = lineptr[nf-1];
               nf--;
          }
          reheap(lineptr, nf, linebuf);
     }
}

/*
 * reheap --
 *   Put the top element of heap to proper place.
 */
void reheap(char *lineptr[], int nf, char linebuf[])
{
     int i, j;
     
     for (i = 0; 2*i+1 < nf; i = j) {
          j = 2*i+1;
          if (j+1 < nf) {
               if (strcmp(lineptr[j], lineptr[j+1]) > 0)
                    j = j + 1;
          }
          if (strcmp(lineptr[i], lineptr[j]) <= 0)
               break;
          char *t = lineptr[i];
          lineptr[i] = lineptr[j];
          lineptr[j] = t;
     }
}

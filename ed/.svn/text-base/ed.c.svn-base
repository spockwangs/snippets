/*
 * ed.c -- A simple text editor.  See Ch.6 of "Software Tools".
 */

#include "ed.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <error.h>
#include <stdlib.h>

#include "pat.h"
#include "clines.h"
#include "buf.h"

#define MAXLINE 1000
#define NO 0

#define APPENDCOM 'a'
#define PERIOD '.'
#define PRINT 'p'
#define NEWLINE '\n'
#define QUIT 'q'
#define DELCOM 'd'
#define INSERT 'i'
#define CHANGE 'c'
#define PRINTCUR '='
#define MOVE 'm'
#define SUBSTITUTE 's'
#define GLOBAL 'g'
#define ENTER 'e'
#define PRINTFIL 'f'
#define READ 'r'
#define WRITE 'w'
#define EXCLUDE 'x'

#define min(a, b) ((a) < (b) ? (a) : (b))

int ckglob(const char line[], int *pi, int *status);
int doglob(const char line[], int i, int *cursav, int *status);
int docmd(const char line[], int i, int glob, int *status);
int defalt(int def1, int def2, int *status);
int doprint(int from, int to);
int append(int line, int glob);
int ckp(const char line[], int i, int *pflag, int *status);
int delete(int from, int to, int *status);
int move(int line3);
int getrhs(const char line[], int *pi, char sub[], int maxsub, int *gflag);
int subst(const char sub[], int gflag);
int getfn(const char line[], int i, char file[]);
int doread(int line, const char file[]);
int dowrite(int from, int to, const char file[]);

char savefile[MAXLINE] = "";

int main(int argc, char *argv[])
{
     char line[MAXLINE];
     int i, status, cursav;
     
     setbf();

     if (argc > 1) {
          strcpy(savefile, argv[1]);
          if (doread(0, savefile) == ERR)
               fputs("?", stdout);
     }
     while (fgets(line, sizeof(line), stdin) != NULL) {
          i = 0;
          cursav = curln;
          if (getlst(line, &i, &status) == OK) {
               if (ckglob(line, &i, &status) == OK)
                    doglob(line, i, &cursav, &status);
               else if (status != ERR)
                    docmd(line, i, NO, &status);
               /* else error, do nothing */
          }
          if (status == ERR) {
               fprintf(stdout, "?\n");
               curln = cursav;
          } else if (status == EOF)
               break;
          /* else OK, loop */
     }

     return 0;
}

/*
 * ckglob --
 *   If global prefix, mark lines to be affected.
 */
int ckglob(const char line[], int *pi, int *status)
{
     int s, gflag, ln, k, i;
     
     i = *pi;
     if (line[i] != GLOBAL && line[i] != EXCLUDE)
          s = EOF;
     else {
          if (line[i] == GLOBAL)
               gflag = 1;
          else
               gflag = 0;
          i++;
          if (optpat(line, &i) == ERR || defalt(1, lastln, &s) == ERR)
               s = ERR;
          else {
               i++;
               for (ln = line1; ln <= line2; ln++) {
                    k = gettxt(ln);
                    if (match(txt, pat) && gflag)
                         buf[k+MARK] = 1;
                    else
                         buf[k+MARK] = 0;
               }
               for (ln = nextln(line2); ln != line1; ln = nextln(ln)) {
                    k = getindex(ln);
                    buf[k+MARK] = 0;
               }
               s = OK;
          }
     }
     *pi = i;
     *status = s;
     return s;
}

/*
 * doglob --
 *   Do command at line[i] on all marked lines.
 */
int doglob(const char line[], int i, int *cursav, int *status)
{
     int s, count, ln, istart, k;

     s = OK;
     count = 0;
     ln = line1;
     istart = i;
     do {
          k = getindex(ln);
          if (buf[k+MARK] == 1) {
               buf[k+MARK] = 0;
               curln = ln;
               *cursav = curln;
               i = istart;
               if (getlst(line, &i, &s) == OK &&
                   docmd(line, i, 1, &s) == OK)
                    count = 0;
          } else {
               ln = nextln(ln);
               count++;
          }
     } while (count <= lastln && s == OK);
     *status = s;
     return s;
}

/*
 * docmd --
 *   Handle all commands except globals.
 */
int docmd(const char line[], int i, int glob, int *status)
{
     int pflag;                 /* Need to print? */
     int gflag;                 /* Globally? */
     int s;
     int line3;
     char sub[MAXLINE], file[MAXLINE];
     
     pflag = NO;
     s = ERR;
     if (line[i] == APPENDCOM) {
          /* Append texts. */
          if (line[i+1] == NEWLINE)
               s = append(line2, glob);
     } else if (line[i] == PRINT) {
          /* Print lines. */
          if (line[i+1] == NEWLINE &&
              defalt(curln, curln, &s) == OK) {
               s = doprint(line1, line2);
          }
     } else if (line[i] == NEWLINE) {
          /* Print next line. */
          if (nlines == 0)
               line2 = nextln(curln);
          s = doprint(line2, line2);
     } else if (line[i] == QUIT) {
          /* Quit. */
          if (line[i+1] == NEWLINE && nlines == 0 && glob == NO)
               s = EOF;
     } else if (line[i] == DELCOM) {
          /* Delete lines. */
          if (ckp(line, i+1, &pflag, &s) == OK &&
              defalt(curln, curln, &s) == OK &&
              delete(line1, line2, &s) == OK &&
              nextln(curln) != 0)
               curln = nextln(curln);
     } else if (line[i] == INSERT) {
          /* Insert lines before current line. */
          if (line[i+1] == NEWLINE)
               s = append(prevln(line2), glob);
     } else if (line[i] == CHANGE) {
          /* Change lines. */
          if (line[i+1] == NEWLINE &&
              defalt(curln, curln, &s) == OK &&
              delete(line1, line2, &s) == OK)
               s = append(prevln(line1), glob);
     } else if (line[i] == PRINTCUR) {
          /* Print current line number. */
          if (ckp(line, i+1, &pflag, &s) == OK) {
               fprintf(stdout, "%d\n", line2);
          }
     } else if (line[i] == MOVE) {
          /* Move lines. */
          i++;
          if (getone(line, &i, &line3, &s) == EOF)
               s = ERR;
          if (s == OK && ckp(line, i, &pflag, &s) == OK &&
              defalt(curln, curln, &s) == OK)
               s = move(line3);
     } else if (line[i] == SUBSTITUTE) {
          i++;
          if (optpat(line, &i) == OK &&
              getrhs(line, &i, sub, sizeof(sub), &gflag) == OK &&
              ckp(line, i+1, &pflag, &s) == OK &&
              defalt(curln, curln, &s) == OK)
               s = subst(sub, gflag);
     } else if (line[i] == ENTER) {
          if (nlines == 0 && getfn(line, i, file) == OK) {
               strcpy(savefile, file);
               clrbuf();
               setbf();
               s = doread(0, file);
          }
     } else if (line[i] == PRINTFIL) {
          if (nlines == 0 && getfn(line, i, file) == OK) {
               strcpy(savefile, file);
               fputs(savefile, stdout);
               putchar('\n');
               s = OK;
          }
     } else if (line[i] == READ) {
          if (getfn(line, i, file) == OK)
               s = doread(line2, file);
     } else if (line[i] == WRITE) {
          if (getfn(line, i, file) == OK &&
              defalt(1, lastln, &s) == OK)
               s = dowrite(line1, line2, file);
     }
     /* else s is error */

     if (s == OK && pflag)
          s = doprint(curln, curln);
     *status = s;
     return s;
}

int defalt(int def1, int def2, int *status)
{
     int s;
     
     if (nlines == 0) {
          line1 = def1;
          line2 = def2;
     }
     if (line1 > line2 || line1 <= 0)
          s = ERR;
     else
          s = OK;
     *status = s;
     return s;
}

/*
 * doprint --
 *   Print lines from 'from' to 'to'.
 */
int doprint(int from, int to)
{
     int i;
     
     if (from <= 0)
          return ERR;
     else {
          for (i = from; i <= to; i++) {
               gettxt(i);
               fputs(txt, stdout);
          }
          curln = to;
          return OK;
     }
}

/*
 * append --
 *   Append lines after 'line'.
 */
int append(int line, int glob)
{
     char lin[MAXLINE];
     int s;
     
     if (glob)
          s = ERR;
     else {
          curln = line;
          for (s = NOSTATUS; s == NOSTATUS;) {
               if (fgets(lin, sizeof(lin), stdin) == NULL)
                    s = EOF;
               else if (lin[0] == PERIOD && lin[1] == NEWLINE)
                    s = OK;
               else if (inject(lin) == ERR)
                    s = ERR;
          }
     }
     return s;
}

/*
 * ckp --
 *   Check for 'p' after command.
 */
int ckp(const char line[], int i, int *pflag, int *status)
{
     if (line[i] == PRINT) {
          i++;
          *pflag = 1;
     } else {
          *pflag = 0;
     }
     if (line[i] == NEWLINE)
          *status = OK;
     else
          *status = ERR;
     return *status;
}

/*
 * delete --
 *   Delete lines from 'from' to 'to.
 */
int delete(int from, int to, int *status)
{
     int k1, k2, s;

     if (from <= 0)
          s = ERR;
     else {
          k1 = getindex(prevln(from));
          k2 = getindex(nextln(to));
          lastln = lastln - (to-from+1);
          curln = prevln(from);
          relink(k1, k2, k1, k2);
          s = OK;
     }
     *status = s;
     return s;
}

/*
 * move --
 *   Move line1 through line2 after line3.
 */
int move(int line3)
{
     int k0, k1, k2, k3, k4, k5;
     
     if (line1 > line2 || line1 <= 0 || line3 > lastln ||
         (line1 < line3 && line3 <= line2))
          return ERR;
     
     if (line1 > lastln)
          line1 = lastln;
     if (line2 > lastln)
          line2 = lastln;
     if (line1 == line3)
          return OK;
     
     k0 = getindex(prevln(line1));
     k3 = getindex(nextln(line2));
     k1 = getindex(line1);
     k2 = getindex(line2);
     relink(k0, k3, k0, k3);
     if (line3 > line1) {
          curln = line3;
          line3 = line3 - (line2-line1+1);
     } else {
          curln = line3 + (line2-line1+1);
     }
     k4 = getindex(line3);
     k5 = getindex(nextln(line3));
     relink(k4, k1, k2, k5);
     relink(k2, k5, k4, k1);
     return OK;
}

/*
 * getrhs --
 *   Get substitution string for 's' command.
 */
int getrhs(const char line[], int *pi, char sub[], int maxsub, int *gflag)
{
     int i, s;

     s = ERR;
     i = *pi;
     if (line[i] == '\0')
          return s;
     if (line[i+1] == '\0')
          return s;
     i = makesub(line, i+1, line[i], sub, maxsub);
     if (i < 0)
          return s;
     if (line[i+1] == GLOBAL) {
          i++;
          *gflag = 1;
     } else {
          *gflag = 0;
     }
     *pi = i;
     return OK;
}

int subst(const char sub[], int gflag)
{
     int s, line, j, k, subbed, m, lastm;
     char new[MAXLINE];

     s = ERR;
     if (line1 <= 0)
          return s;
     for (line = line1; line <= line2; line++) {
          j = 0;
          subbed = 0;
          gettxt(line);
          lastm = 0;
          for (k = 0; txt[k] != '\0';) {
               if (gflag || subbed == 0) {
                    m = amatch(txt, k, pat);
               } else {
                    m = -1;
               }
               if (m > 0 && lastm != m) {
                    subbed = 1;
                    catsub(txt, k, m, sub, new, &j, sizeof(new));
                    lastm = m;
               }
               if (m < 0 || m == k) {
                    addset(txt[k], new, &j, sizeof(new));
                    k++;
               } else {
                    k = m;
               }
          }
          if (subbed) {
               if (addset('\0', new, &j, sizeof(new)) < 0) {
                    s = ERR;
                    break;
               }
               delete(line, line, &s);
               s = inject(new);
               if (s == ERR)
                    break;
               s = OK;
          }
     }
     return s;
}

/*
 * getfn --
 *   Get file name from line[i].
 */
int getfn(const char line[], int i, char file[])
{
     int j, k, s;

     s = ERR;
     if (isblank(line[i+1])) {
          j = i + 2;
          skipblank(line, &j);
          for (k = 0; line[j] != '\n'; k++) {
               file[k] = line[j];
               j++;
          }
          file[k] = '\0';
          if (k > 0)
               s = OK;
     } else if (line[i+1] == NEWLINE && savefile[0] != '\0') {
          strcpy(file, savefile); /* old file name */
          s = OK;
     }
     /* else error */
     if (s == OK && savefile[0] == '\0')
          strcpy(savefile, file); /* save if no old one */
     return s;
}

/*
 * doread --
 *   Read 'file' after 'ln'.
 */
int doread(int ln, const char file[])
{
     int count, s;
     FILE *fp;
     char line[MAXLINE];

     fp = fopen(file, "r");
     if (fp == NULL)
          s = ERR;
     else {
          curln = ln;
          s = OK;
          for (count = 0; fgets(line, sizeof(line), fp) != NULL; count++) {
               s = inject(line);
               if (s == ERR)
                    break;
          }
          fclose(fp);
          printf("%d\n", count);
     }
     return s;
}

/*
 * dowrite --
 *   Write 'from' through 'to' into 'file'.
 */
int dowrite(int from, int to, const char file[])
{
     FILE *fp;
     int line, s;

     fp = fopen(file, "w");
     if (fp == NULL)
          s = ERR;
     else {
          for (line = from; line <= to; line++) {
               gettxt(line);
               fputs(txt, fp);
          }
          fclose(fp);
          printf("%d\n", to-from+1);
          s = OK;
     }
     return s;
}

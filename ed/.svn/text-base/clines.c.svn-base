#include "clines.h"
#include "ed.h"
#include "pat.h"
#include <ctype.h>

#define CURLINE '.'
#define LASTLINE '$'
#define SCAN '/'
#define BACKSCAN '\\'
#define COMMA ','
#define SEMICOL ';'
#define PLUS '+'
#define MINUS '-'
#define PERIOD '.'

#define min(a, b) ((a) < (b) ? (a) : (b))

int line1;
int line2;
int nlines;
int curln;
int lastln;

/*
 * getlst --
 *   Collect line numbers (if any) at line[i] and increment i.
 */
int getlst(const char line[], int *pi, int *status)
{
     int num;
     
     line2 = 0;
     for (nlines = 0; getone(line, pi, &num, status) == OK;) {
          line1 = line2;
          line2 = num;
          nlines++;
          if (line[*pi] != COMMA && line[*pi] != SEMICOL)
               break;
          if (line[*pi] == SEMICOL)
               curln = num;
          (*pi)++;
     }
     nlines = min(nlines, 2);
     if (nlines == 0)
          line2 = curln;
     if (nlines <= 1)
          line1 = line2;
     if (*status != ERR)
          *status = OK;
     return *status;
}

/*
 * getone --
 *   Evaluate one line number expression.
 */
int getone(const char line[], int *pi, int *pnum, int *status)
{
     int i, istart, mul, num;

     i = *pi;
     istart = i;
     *pnum = 0;
     skipblank(line, &i);
     if (getnum(line, &i, pnum, status) == OK) {
          do {
               skipblank(line, &i);
               if (line[i] != PLUS && line[i] != MINUS) {
                    *status = EOF;
                    break;
               }
               if (line[i] == PLUS)
                    mul = 1;
               else
                    mul = -1;
               i++;
               skipblank(line, &i);
               if (getnum(line, &i, &num, status) == OK)
                    *pnum += mul * num;
               if (*status == EOF)
                    *status = ERR;
          } while (*status == OK);
     }
     if (*pnum < 0 || *pnum > lastln)
          *status = ERR;

     *pi = i;
     if (*status == ERR)
          return ERR;
     else if (i <= istart) {
          *status = EOF;
     } else {
          *status = OK;
     }
     return *status;
}

/*
 * skipblank --
 *   Skip blanks and advance pi.
 */
void skipblank(const char line[], int *pi)
{
     int i = *pi;

     while (isblank(line[i]))
          i++;
     *pi = i;
}

/*
 * getnum --
 *   Convert one term to a line number.
 */
int getnum(const char line[], int *pi, int *pnum, int *status)
{
     int i, s;
     const char *digits = "0123456789";

     s = OK;
     if (index2(digits, line[i]) >= 0) {
          *pnum = ctoi(line, &i);
          i--;                  /* move back; to be advanced at the end */
     } else if (line[i] == CURLINE) {
          *pnum = curln;
     } else if (line[i] == LASTLINE) {
          *pnum = lastln;
     } else if (line[i] == SCAN || line[i] == BACKSCAN) {
          if (optpat(line, &i) == ERR) { /* build the pattern */
               s = ERR;
          } else if (line[i] == SCAN) {
               s = ptscan(FORWARD, pnum);
          } else {
               s = ptscan(BACKWARD, pnum);
          }
     } else {
          s = EOF;
     }
     if (s == OK)
          i++;
     *pi = i;
     *status = s;
     return s;
}

/*
 * ctoi --
 *   Convert string at line[i] to integer.
 */
int ctoi(const char line[], int *pi)
{
     const char *digits = "0123456789";
     int i, d, n;

     i = *pi;
     while (isblank(line[i]))
          i++;
     for (n = 0; line[i] != '\0'; i++) {
          d = index2(digits, line[i]);
          if (d < 0)            /* non-digit */
               break;
          n = n*10 + d;
     }
     *pi = i;
     return n;
}

/*
 * nextln --
 *   Get line after 'line'.
 */
int nextln(int line)
{
     line++;
     if (line > lastln)
          line = 0;
     return line;
}

/*
 * prevln --
 *   Get line before 'line'.
 */
int prevln(int line)
{
     line--;
     if (line < 0)
          line = lastln;
     return line;
}

#include "pat.h"

#include <stdlib.h>
#include <error.h>

#include "ed.h"
#include "clines.h"
#include "buf.h"

#define MAXPAT 100
#define NOT '^'
#define CCLEND ']'
#define DASH '-'
#define ESCAPE '\\'
#define BOL '^'
#define EOL '$'
#define ANY '.'
#define CLOSURE '*'
#define AND '&'

#define CHAR 'a'
#define CCL '['
#define NCCL 'n'
#define DITTO -1

#define CLOSIZE 4

char pat[MAXPAT];

/*
 * optpat --
 *   Make a pattern if specified at line[i].
 */
int optpat(const char line[], int *pi)
{
     int i, s;

     i = *pi;
     if (line[i] == '\0')
          s = ERR;
     else if (line[i+1] == '\0')
          s = ERR;
     else if (line[i+1] == line[i])
          i++;
     else
          i = makepat(line, i+1, line[i], pat, MAXPAT);
     if (pat[0] == '\0')
          s = ERR;
     if(s == ERR) {
          pat[0] = '\0';
     } else
          s = OK;
     *pi = i;
     return s;
}

/*
 * ptscan --
 *   Scan for next occurrence of pattern.
 */
int ptscan(int way, int *pnum)
{
     int k, n;

     n = curln;
     do {
          if (way == FORWARD) {
               n = nextln(n);
          } else {
               n = prevln(n);
          }
          k = gettxt(n);        /* get text of line 'n' in 'txt' */
          if (match(txt, pat)) {
               *pnum = n;
               return OK;
          }
     } while (n != curln);
     return ERR;
}

/*
 * makepat --
 *   Make pattern from 'arg[from]' to delim. Return index of next
 *   unexamined input arg, or -1 on error.
 */
int makepat(const char arg[], int from, char delim, char pat[], int maxpat)
{
     int i, j, lastcl, lastj, lj;

     j = 0;                     /* pattern index */
     lastj = 0;
     lastcl = 0;
     for (i = from; arg[i] != delim && arg[i] != '\n'; i++) {
          lj = j;
          if (arg[i] == ANY)
               addset(ANY, pat, &j, maxpat);
          else if (arg[i] == BOL && i == from)
               addset(BOL, pat, &j, maxpat);
          else if (arg[i] == EOL && arg[i+1] == delim)
               addset(EOL, pat, &j, maxpat);
          else if (arg[i] == CCL) {
               if (getccl(arg, &i, pat, &j, maxpat) < 0)
                    break;
          } else if (arg[i] == CLOSURE && i > from) {
               lj = lastj;
               if (pat[lj] == BOL || pat[lj] == EOL || pat[lj] == CLOSURE)
                    break;
               lastcl = stclos(pat, &j, lastj, lastcl, maxpat);
          } else {
               addset(CHAR, pat, &j, maxpat);
               addset(esc(arg, &i), pat, &j, maxpat);
          }
          lastj = lj;
     }
     if (arg[i] != delim)
          return -1;
     else if (addset('\0', pat, &j, maxpat) < 0)
          return -1;
     return i;
}

/*
 * getccl --
 *   Expand char class at arg[*pi] into pat[*pj].  Return 0 if OK, or -1 on
 *   error.
 */
int getccl(const char arg[], int *pi, char pat[], int *pj, int maxpat)
{
     int jstart;
     
     (*pi)++;                       /* skip over '[' */
     if (arg[*pi] == NOT) {
          addset(NCCL, pat, pj, maxpat);
          (*pi)++;
     } else
          addset(CCL, pat, pj, maxpat);
     jstart = *pj;
     addset(0, pat, pj, maxpat);
     fillset(CCLEND, arg, pi, pat, pj, maxpat);
     pat[jstart] = *pj - jstart - 1;
     if (arg[*pi] == CCLEND)
          return 0;
     else
          return -1;
}

/*
 * fillset --
 *   Expand set at array[i] into set[j], stop at delim.
 */
void fillset(char delim, const char array[], int *pi, char set[], int *pj, int maxset)
{
     const char *digits = "0123456789";
     const char *lowhalf = "abcdefghijklmnopqrstuvwxyz";
     const char *uphal = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

     for (; array[*pi] != delim && array[*pi] != '\0'; (*pi)++) {
          if (array[*pi] == ESCAPE)
               addset(esc(array, pi), set, pj, maxset);
          else if (array[*pi] != DASH)
               addset(array[*pi], set, pj, maxset);
          else if (*pj <= 0 || array[*pi+1] == '\0')
               addset(DASH, set, pj, maxset);
          else if (index2(digits, set[*pj-1]) >= 0)
               dodash(digits, array, pi, set, pj, maxset);
          else if (index2(lowhalf, set[*pj-1]) >= 0)
               dodash(lowhalf, array, pi, set, pj, maxset);
          else if (index2(uphal, set[*pj-1]) >= 0)
               dodash(uphal, array, pi, set, pj, maxset);
          else
               addset(DASH, set, pj, maxset);
     }
}

/*
 * esc --
 *   Return escaped array[*pi] and advance *pi.
 */
char esc(const char array[], int *pi)
{
     int i = *pi;
     if (array[i] != ESCAPE)
          return array[i];
     else if (array[i+1] == '\0')
          return ESCAPE;
     *pi = ++i;
     if (array[i] == 'n')
          return '\n';
     else if (array[i] == 't')
          return '\t';
     return array[i];
}

/*
 * dodash --
 *   Expand array[*pi-1] - array[*pi+1] to set[j] ...
 */
void dodash(const char *alph, const char array[], int *pi, char set[], int *pj, int maxset)
{
     int k, limit;
     (*pi)++;
     (*pj)--;
     limit = index2(alph, esc(array, pi));
     for (k = index2(alph, set[*pj]); k <= limit; k++)
          addset(alph[k], set, pj, maxset);
}

/*
 * addset --
 *   Add 'c' to 'set[*pi]' if any space and advance *pi.
 */
int addset(char c, char set[], int *pi, int maxsize)
{
     int i = *pi;

     if (i > maxsize-1)
          return -1;
     else {
          set[i] = c;
          i++;
          *pi = i;
          return 0;
     }
}
               
/*
 * stclos --
 *   Insert closure entry at pat[j].
 */
int stclos(char pat[], int *pj, int lastj, int lastcl, int maxpat)
{
     int jp, jt;

     for (jp = *pj-1; jp >= lastj; jp--) {
          jt = jp + CLOSIZE;
          addset(pat[jp], pat, &jt, maxpat);
     }
     *pj += CLOSIZE;
     jt = lastj;
     addset(CLOSURE, pat, &lastj, maxpat);
     addset(0, pat, &lastj, maxpat);
     addset(lastcl, pat, &lastj, maxpat);
     addset(0, pat, &lastj, maxpat);
     return jt;
}

/*
 * index2 --
 *   Return index of char c in str if found, or -1 if not.
 */
int index2(const char str[], char c)
{
     int i;

     for (i = 0; str[i] != '\0'; i++)
          if (str[i] == c)
               return i;
     return -1;
}

/*
 * patsize --
 *   Return size of pattern entry at pat[n].
 */
int patsize(const char pat[], int n)
{
     if (pat[n] == CHAR)
          return 2;
     else if (pat[n] == BOL || pat[n] == EOL || pat[n] == ANY)
          return 1;
     else if (pat[n] == CCL || pat[n] == NCCL)
          return pat[n+1] + 2;
     else if (pat[n] == CLOSURE)
          return CLOSIZE;
     error(1, 0, "in patsize: can't happen.");
     return -1;
}

/*
 * match --
 *   Match 'pattern' anywhere in 'line'.
 */
int match(const char line[], const char pattern[])
{
     int i;

     for (i = 0; line[i] != '\0'; i++) {
          if (amatch(line, i, pattern) >= 0)
               return 1;
     }
     return 0;
}

/*
 * amatch --
 *   Match 'pattern' from 'from' of 'line'.  Return index of next
 *   unexamined char if matched, -1 if not matched.
 */
int amatch(const char line[], int from, const char pattern[])
{
     int i, j, k, offset;

     offset = from;
     for (j = 0; pattern[j] != '\0'; j += patsize(pattern, j)) {
          if (pattern[j] == CLOSURE) {
               j += CLOSIZE;
               for (i = offset; line[i] != '\0';) {
                    if (omatch(line, &i, pattern, j) == 0)
                         break;
               }

               j += patsize(pattern, j);
               for (; i >= offset; i--) {
                    k = amatch(line, i, pattern+j);
                    if (k >= 0)
                         break;
               }
               offset = k;
               break;
          } else if (omatch(line, &offset, pattern, j) == 0)
               return -1;
     }
     return offset;
}

/*
 * omatch --
 *   Try to match a signle pattern at pattern[j] and advance the input
 *   position 'pi'.  Return 1 if matched, or 0 if not.
 */
int omatch(const char line[], int *pi, const char pattern[], int j)
{
     int i;
     int bump;

     i = *pi;
     bump = -1;
     if (line[i] == '\0')
          return 0;

     switch (pattern[j]) {
     case CHAR:
          if (line[i] == pattern[j+1])
               bump = 1;
          break;
     case BOL:
          if (i == 0)
               bump = 0;
          break;
     case ANY:
          if (line[i] != '\n')
               bump = 1;
          break;
     case EOL:
          if (line[i] == '\n')
               bump = 0;
          break;
     case CCL:
          if (locate(line[i], pattern, j+1) == 1)
               bump = 1;
          break;
     case NCCL:
          if (line[i] != '\n' && locate(line[i], pattern, j+1) == 0)
               bump = 1;
          break;
     default:
          fprintf(stderr, "in omatch: can't happen.\n");
          exit(1);
     }
     if (bump >= 0) {
          i += bump;
          *pi = i;
          return 1;
     }
     return 0;
}

/*
 * locate --
 *   Look for 'c' in char class at 'pat[offset]'.
 */
int locate(char c, const char pat[], int offset)
{
     int i;
     for (i = offset+pat[offset]; i > offset; i--) {
          if (c == pat[i])
               return 1;
     }
     return 0;
}

/*
 * makesub --
 *   Make substitution from arg[from] until delim into sub[].  Return next
 *   unexamined index of arg[].
 */
int makesub(const char arg[], int from, char delim, char sub[], int maxsize)
{
     int i, j;
     j = 0;
     for (i = from; arg[i] != delim && arg[i] != '\0'; i++) {
          if (arg[i] == AND)
               addset(DITTO, sub, &j, maxsize);
          else
               addset(esc(arg, &i), sub, &j, maxsize);
     }
     if (arg[i] != delim)
          return -1;
     else if (addset('\0', sub, &j, maxsize) < 0)
          return -1;
     return i;
}

/*
 * catsub --
 *   Add replacement text to end of new.
 */
void catsub(const char line[], int from, int to, const char sub[], char new[], int *pk, int maxnew)
{
     int i, j;
     for (i = 0; sub[i] != '\0'; i++) {
          if (sub[i] == DITTO)
               for (j = from; j < to; j++)
                    addset(line[j], new, pk, maxnew);
          else
               addset(sub[i], new, pk, maxnew);
     }
}

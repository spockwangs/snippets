#include "buf.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "clines.h"
#include "pat.h"

#define MAXBUF 10000000
#define MAXLINE 1000

#define NEWLINE '\n'

#define PREV 0
#define NEXT sizeof(int)
#define MARK (NEXT+sizeof(int))
#define SEEKADR (MARK+1)
#define LENG (SEEKADR+sizeof(int))
#define LINE0 0
#define BUFENT 17

int makeline(const char line[], int i, int *newindex);

char txt[MAXLINE];
char buf[MAXBUF];
int lastbf;
FILE *sfp;
int scrend;

void clrbuf(void)
{
     fclose(sfp);
}

int getindex(int line)
{
     int j, k;

     k = LINE0;
     for (j = 0; j < line; j++)
          k = *((int *) &buf[k+NEXT]);
     
     return k;
}

int gettxt(int line)
{
     int i, j;

     i = getindex(line);
     fseek(sfp, *((int *) &buf[i+SEEKADR]), SEEK_SET);
     fread(txt, 1, *((int *) &buf[i+LENG]), sfp);
     j = *((int *) &buf[i+LENG]);
     txt[j] = '\0';
     return i;
}

void relink(int a, int x, int y, int b)
{
     *((int *) &buf[x+PREV]) = a;
     *((int *) &buf[y+NEXT]) = b;
}

/*
 * setbf --
 *   Initialize line storage buffer.
 */
void setbf(void)
{
     int k;
     
     sfp = tmpfile();
     if (sfp == NULL) {
          perror("tmpfile()");
          exit(1);
     }
     scrend = 0;
     lastbf = LINE0;
     makeline("", 0, &k);
     relink(k, k, k, k);
     curln = 0;
     lastln = 0;
}

int inject(const char line[])
{
     int i, k1, k2, k3, s;

     for (i = 0; line[i] != '\0';) {
          i = makeline(line, i, &k3);
          if (i < 0) {
               s = ERR;
               break;
          }
          k1 = getindex(curln);
          k2 = getindex(nextln(curln));
          relink(k1, k3, k3, k2);
          relink(k3, k2, k1, k3);
          curln++;
          lastln++;
          s = OK;
     }
     return s;
}

/*
 * makeline --
 *   Make new line entry.
 */
int makeline(const char line[], int i, int *newindex)
{
     int txtend, s;

     s = ERR;
     if (lastbf + BUFENT > MAXBUF-1)
          return s;
     txtend = 0;
     for (; line[i] != '\0';) {
          addset(line[i], txt, &txtend, MAXLINE);
          i++;
          if (line[i-1] == NEWLINE)
               break;
     }
     if (addset('\0', txt, &txtend, MAXLINE) < 0)
          return s;
     fseek(sfp, scrend, SEEK_SET);
     *((int *) &buf[lastbf+SEEKADR]) = scrend;
     *((int *) &buf[lastbf+LENG]) = strlen(txt);
     fputs(txt, sfp);
     scrend += *((int *) &buf[lastbf+LENG]);
     buf[lastbf+MARK] = 0;
     *newindex = lastbf;
     lastbf += BUFENT;
     return i;
}

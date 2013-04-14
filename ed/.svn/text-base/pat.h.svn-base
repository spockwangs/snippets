#ifndef _PAT_H
#define _PAT_H

#define FORWARD 0
#define BACKWARD 1

extern char pat[];

int optpat(const char line[], int *pi);
int ptscan(int way, int *pnum);
int makepat(const char arg[], int from, char delim, char pat[], int maxpat);
int getccl(const char arg[], int *pi, char pat[], int *pj, int maxpat);
void fillset(char delim, const char array[], int *pi, char set[], int *pj, int maxset);
char esc(const char array[], int *pi);
void dodash(const char *alph, const char array[], int *pi, char set[], int *pj, int maxset);
int addset(char c, char set[], int *pi, int maxsize);
int stclos(char pat[], int *pj, int lastj, int lastcl, int maxpat);
int index2(const char str[], char c);
int patsize(const char pat[], int n);
int match(const char line[], const char pattern[]);
int amatch(const char line[], int from, const char pattern[]);
int omatch(const char line[], int *pi, const char pattern[], int j);
int locate(char c, const char pat[], int offset);
int makesub(const char arg[], int from, char delim, char sub[], int maxsize);
void catsub(const char line[], int from, int to, const char sub[], char new[], int *pk, int maxnew);

#endif

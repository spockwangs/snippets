#ifndef _BUF_H
#define _BUF_H

#include "ed.h"

#define NEXT sizeof(int)
#define MARK (NEXT+sizeof(int))

extern char txt[];
extern char buf[];

void clrbuf(void);
int getindex(int line);
int gettxt(int line);
void relink(int a, int x, int y, int b);
void setbf(void);
int inject(const char line[]);

#endif

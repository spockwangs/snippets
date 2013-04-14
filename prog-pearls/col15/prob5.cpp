/*
 * prob5.cpp -- Problem 5 of column
 */


/* Copyright (C) 1999 Lucent Technologies */
/* From 'Programming Pearls' by Jon Bentley */

/* wordfreq.c -- list of words in file, with counts */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <error.h>
#include <errno.h>
#include <assert.h>
#include <ctype.h>

#define WORD_WIDTH 15           // max width of words; for printing words

typedef struct node *nodeptr;
typedef struct node {
    char *word;
    int count;
    nodeptr next;
} node;

#define NHASH 29989
#define MULT 31
nodeptr bin[NHASH];

unsigned int hash(char *p)
{	
    unsigned int h = 0;
    for ( ; *p; p++)
        h = MULT * h + *p;
    return h % NHASH;
}

#define NODEGROUP 1000
int nodesleft = 0;
nodeptr freenode;

nodeptr nmalloc()
{	
    if (nodesleft == 0) {
        freenode = (node *) malloc(NODEGROUP*sizeof(node));
        nodesleft = NODEGROUP;
    }
    nodesleft--;
    return freenode++;
}

#define CHARGROUP 10000
int charsleft = 0;
char *freechar;

char *smalloc(int n)
{	
    if (charsleft < n) {
        freechar = (char *) malloc(n+CHARGROUP);
        charsleft = n+CHARGROUP;
    }
    charsleft -= n;
    freechar += n;
    return freechar - n;
}

/*
 * Insert the word 's' into the hash table.
 * Return true if 's' already exists, or flase otherwise.
 */
bool incword(char *s)
{	
    nodeptr p;
    int h = hash(s);
    for (p = bin[h]; p != NULL; p = p->next)
        if (strcmp(s, p->word) == 0) {
            (p->count)++;
            return false;
        }

    p = nmalloc();
    p->count = 1;
    p->word = smalloc(strlen(s)+1);
    strcpy(p->word, s);
    p->next = bin[h];
    bin[h] = p;
    return true;
}


int getword(char *word)
{
    int c, i;
    while ((c = getchar()) != EOF && !isalpha(c))
        ;
    if (c != EOF) {
        i = 0;
        word[i++] = c;
        while ((c = getchar()) != EOF) {
            if (isalpha(c))
                word[i++] = c;
            else 
                break;
        }
        word[i] = '\0';
        return c;
    } else
        return EOF;
}
        
struct word_freq {
    char *word;
    int count;
};

int freqcmp(const void *p1, const void *p2)
{
    const word_freq *p = (const word_freq *)p1;
    const word_freq *q = (const word_freq *)p2;
    if (p->count < q->count)
        return 1;
    else if (p->count == q->count)
        return 0;
    else
        return -1;
}

int main()
{	
    int i, nwords;
    nodeptr p;
    char buf[100];
    for (i = 0; i < NHASH; i++)
        bin[i] = NULL;

    nwords = 0;
    while (getword(buf) != EOF) {
        if (incword(buf))
            nwords++;
    }
    
    /*
     * Put the word in decreasing count order.
     */
    word_freq *pfreq = (word_freq *) malloc(nwords*sizeof(*pfreq));
    if (pfreq == NULL)
        error(1, errno, "malloc failed");
    int n;
    for (n = 0, i = 0; i < NHASH; i++)
        for (p = bin[i]; p != NULL; p = p->next) {
            pfreq[n].word = p->word;
            pfreq[n].count = p->count;
            n++;
        }
    assert(n == nwords);
    qsort(pfreq, n, sizeof(word_freq), freqcmp);
    for (i = 0; i < nwords; i++)
        printf("%-*s %d\n", WORD_WIDTH, pfreq[i].word, pfreq[i].count);
    free(pfreq);
    
    return 0;
}

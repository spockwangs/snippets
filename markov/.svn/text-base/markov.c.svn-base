/*
 * markov
 *   From Chapter 3 of "The practice of programming".
 *
 *   The difference from the original version is that all words are
 *   stored in a separate hash table, "wordtab", with each different
 *   word occurs only once.  So when we search in the prefix table we
 *   only need to compare pointers to strings to decide if the strings
 *   are equal, leading to a faster program, I hope.
 *
 * Usage
 *   ./markov < file
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <err.h>

        /* defines */

enum {
    NPREF   = 2,        // # of prefix words
    NHASH   = 4093,     // sizeof state hash table array
    MAXGEN  = 1000,     // max # words generated
    MULTIPLIER = 31,    // used in hash()
};

typedef struct State State;
typedef struct Suffix Suffix;
struct State {  // prefix + suffix list
    char    *pref[NPREF];   // prefix words
    Suffix  *suf;           // list of suffixes
    State   *next;          // next in hash table
};
struct Suffix { // list of suffixes
    char    *word;      // suffix
    Suffix  *next;      // next in list of suffixes
};

typedef struct Wchain Wchain;
struct Wchain {  // collision chains of words for word table
    char *word;
    Wchain *next;
};


        /* globals */

State *statetab[NHASH];     // hashtable for states
Wchain *wordtab[NHASH];     // hash table for words
char NONWORD[] = "\n";      // cannot appear as real words

        
        /* function prototypes */

char *strdup(char *);
unsigned int hash(char *s[NPREF]);
unsigned int hash2(char *s);
State *lookup(char *prefix[NPREF], int create);
void build(char *prefix[NPREF], FILE *f);
void add(char *prefix[NPREF], char *suffix);
void addsuffix(State *sp, char *suffix);
void generate(int nwords);


/*
 * hash2 --
 *   Compute hash value for a string.
 */
unsigned int hash2(char *s)
{
    unsigned char *p;
    unsigned int h;

    h = 0;
    for (p = (unsigned char *) s; *p != '\0'; p++)
        h = MULTIPLIER * h + *p;
    return h % NHASH;
}


/*
 * hash --
 *   Compute hash value for array of NPREF strings.
 */
unsigned int hash(char *s[NPREF])
{
    unsigned int h;
    unsigned char *p;
    int i;

    h = 0;
    for (i = 0; i < NPREF; i++) {
        for (p = (unsigned char *) s[i]; *p != '\0'; p++)
            h = MULTIPLIER * h + *p;
    }
    return h % NHASH;
}


/*
 * lookup_word --
 *   Lookup a word in the word table.  If not found add the word into
 *   the table.  Return a pointer to it.  Creation strdup the word.
 */
char *lookup_word(char *word)
{
    int h;
    Wchain *wp;

    h = hash2(word);
    for (wp = wordtab[h]; wp != NULL; wp = wp->next) {
        if (strcmp(word, wp->word) == 0)    // found it
            return wp->word;
    }
    wp = (Wchain *) malloc(sizeof *wp);
    if (wp == NULL)
        err(1, "malloc failure");
    wp->word = strdup(word);
    if (wp->word == NULL)
        err(1, "strdup failure");
    wp->next = wordtab[h];
    wordtab[h] = wp;
    return wp->word;
}


/*
 * lookup --
 *   Search for prefix; create if requested.  Return pointer if
 *   present or created; NULL if not.  Creation doesn't strdup so
 *   string mustn't change later.
 */
State *lookup(char *prefix[NPREF], int create)
{
    int i, h;
    State *sp;

    h = hash(prefix);
    for (sp = statetab[h]; sp != NULL; sp = sp->next) {
        /*
         * All words are in the wordtab and each different word only
         * occur once, so we can just compare pointers.
         */
        for (i = 0; i < NPREF; i++) {
            if (prefix[i] != sp->pref[i])
                break;
        }
        if (i == NPREF)     // found it
            return sp;
    }
    if (create) {
        sp =  (State *) malloc(sizeof(State));
        if (sp == NULL)
            err(1, "malloc failure");
        for (i = 0; i < NPREF; i++)
            sp->pref[i] = prefix[i];
        sp->suf = NULL;
        sp->next = statetab[h];
        statetab[h] = sp;
    }
    return sp;
}


/*
 * build --
 *   Read input, build prefix table.
 */
void build(char *prefix[NPREF], FILE *f)
{
    char buf[100], fmt[10];

    // create a format string; %s could overflow buf
    sprintf(fmt, "%%%ds", sizeof(buf)-1);
    while (fscanf(f, fmt, buf) != EOF)
        add(prefix, lookup_word(buf));
}


/* add --
 *   Add word to suffix list, update prefix
 */
void add(char *prefix[NPREF], char *suffix)
{
    State *sp;

    sp = lookup(prefix, 1);     // create if not found
    addsuffix(sp, suffix);

    // move the words down the prefix
    memmove(prefix, prefix+1, (NPREF-1)*sizeof(prefix[0]));
    prefix[NPREF-1] = suffix;
}


/*
 * addsufix --
 *   Add to state, suffix must not change later.
 */
void addsuffix(State *sp, char *suffix)
{
    Suffix *suf;

    suf = (Suffix *) malloc(sizeof(*suf));
    if (suf == NULL)
        err(1, "malloc failure");
    suf->word = suffix;
    suf->next = sp->suf;
    sp->suf = suf;
}


/* 
 * generate
 *   Produce output, one word per line.
 */
void generate(int nwords)
{
    State *sp;
    Suffix *suf;
    char *prefix[NPREF], *w, *nonword;
    int i, nmatch;

    nonword = lookup_word(NONWORD);
    for (i = 0; i < NPREF; i++) {   // reset initial prefix
        prefix[i] = nonword;
    }

    for (i = 0; i < nwords; i++) {
        sp = lookup(prefix, 0);
        nmatch = 0;
        for (suf = sp->suf; suf != NULL; suf = suf->next) {
            if (rand() % ++nmatch == 0) {   // Pr. = 1/nmatch
                w = suf->word;
            }
        }
        if (w == nonword)
            break;
        printf("%s\n", w);
        memmove(prefix, prefix+1, (NPREF-1)*sizeof(prefix[0]));
        prefix[NPREF-1] = w;
    }
}


int main(void)
{
    int i, nwords = MAXGEN;
    char *prefix[NPREF];        // current input prefix
    char *nonword = lookup_word(NONWORD);
    
    srand(time(NULL));
    for (i = 0; i < NPREF; i++)
        prefix[i] = nonword;
    build(prefix, stdin);
    add(prefix, nonword);
    generate(nwords);
    return 0;
}

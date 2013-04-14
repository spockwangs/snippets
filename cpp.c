/*
 * cpp.c -- A simple Ratfor preprocessor.
 * 
 * A simple Ratfor preprocessor, adpated from Chapter 8 of "Software
 * Tools".  The original code is written in PL/I.
 *
 * The syntax of this preprocessor is like this:
 *     define(name, definition)
 * where whenever name appears it is replaced by its definiton.  For macros
 * with arguments, the argument is represented by $n, where n is a
 * number, and will be replaced by the nth argument when the macro is
 * actually called.  For more details see Chapter 8 of "Software Tools".
 *
 * when: 2010-10-01 17:18:35
 */

#include <stdio.h>
#include <string.h>
#include <assert.h>

#define MAXDEF 200
#define MAXTOK 100

enum {
     ALPHA = 'a',
     DEFTYPE = -2,
};

void puttok(const char *s);
int lookup(const char *name, char def[MAXDEF]);
void install(const char *name, const char *def);
void putchr(char c);
void dodef(const int argstack[], int i, int j);

/* ------------------------------ */

/*
 * Input/Output routines.
 */

/*
 * Get next token in 'token'.  Return type of the token.
 */
int get_token(char *token, int size)
{
     assert(token == NULL || size > 0);
     
     int i, c;

     i = 0;
     for (i = 0; i < size-1; i++) {
          c = getchar();
          if (!isalnum(c))
               break;
          if (token != NULL)
               token[i] = (char) c;
     }

     if (token != NULL && i >= size-1)
          error(1, 0, "token too long");
     if (i == 0) {
          /* Non-alpha */
          if (c != EOF)
               token[i++] = (char) c;
     } else {
          /* some alpha was seen */
          ungetc(c, stdin);
          c = ALPHA;
     }
     if (token != NULL)
          token[i] = '\0';
     return c;
}
          
void ungetstr(const char *s)
{
     assert(s != NULL);

     int i;
     for (i = strlen(s)-1; i >= 0; i--)
          ungetc(s[i], stdin);
}


/* ------------------------------ */

/*
 * Expand macros with arguments.
 */

#define ARGSIZE 100
#define CALLSIZE 10
#define EVALSIZE 1000
#define ARGFLAG '$'

int cp;                  /* current all stack pointer */
int ep;                  /* next free position in evalst */
char evalst[EVALSIZE];   /* evaluation stack */

/*
 * Put a token either on output or into evaluation stack.
 */
void puttok(const char *s)
{
     assert(s != NULL);
     
     int i;
     for (i = 0; s[i] != '\0'; i++) {
          putchr(s[i]);
     }
}

/*
 * Put single char on output or into evaluation stack.
 */
void putchr(char c)
{
     if (cp == -1) {
          putchar(c);
     } else {
          if (ep >= EVALSIZE) {
               error(1, 0, "evaluation stack overflow");
          }
          evalst[ep++] = c;
     }
}

/*
 * Push ep onto argstack, return new pointer ap.
 */
int push(int ep, int argstack[], int ap)
{
     assert(argstack != NULL);

     if (ap >= ARGSIZE) {
          error(1, 0, "arg stack overflow");
     }
     argstack[ap++] = ep;
     return ap;
}

/*
 * Expand args i through j: evaluate builtin or push back defn.
 * argstack[i] points to the definition and argstack[i+1] points to the
 * name.  argstack[i+2] through argstack[j] are the arguments.
 */
void eval(const int argstack[], int i, int j)
{
     assert(argstack != NULL);
     assert(i >= 0 && j > i);

     int argno, k, m, n, t, td;
     char args[10] = "";        /* hold argument number */

     t = argstack[i];
     td = evalst[t];
     if (td == DEFTYPE) {
          dodef(argstack, i, j);
     } else {
          /*
           * Push back replacement texts to stdin.
           * NOTE: This has to be done in reverse order.
           */
          int l = sizeof(args)/sizeof(args[0])-1;
          for (k = t+strlen(&evalst[t])-1; k >= t; k--) {
               if (isdigit(evalst[k])) {
                    args[--l] = evalst[k];
               } else if (evalst[k] == ARGFLAG) {
                    /* Expand arguments. */
                    argno = atoi(args+l);
                    l = sizeof(args)/sizeof(args[0])-1;
                    if (argno >= 0 && argno < j-i) {
                         n = i + argno + 1;
                         m = argstack[n];
                         ungetstr(&evalst[m]);
                    }
               } else {
                    /* Clear args. */
                    ungetstr(args+l);
                    l = sizeof(args)/sizeof(args[0])-1;

                    ungetc(evalst[k], stdin);
               }
          }
     }
}

#define MAXARGLEN 200
#define MAXARGS 20

/*
 * Install definition in table. argstack[i] points to the definition and
 * argstack[i+1] points to the name.  argstack[i+2] through argstack[j] are
 * the arguments.
 */
void dodef(const int argstack[], int i, int j)
{
     assert(argstack != NULL);

     char name[MAXTOK];         /* name */
     char defn[MAXDEF] = "";    /* and its definition */
     char args[MAXARGLEN];      /* hold macro arguments */
     int argptr[MAXARGS];       /* point into args; argptr[0] points to the
                                 * first argument, argptr[1] the second and
                                 * son on. */

     int a2, a3, k, n, l;
     char *p = NULL;
     char token[MAXTOK];
     
     if (j-i <= 2)
          return;
     a2 = argstack[i+2];
     a3 = argstack[i+3];

     /* Get the name. */
     p = &evalst[a2];
     while (!isalnum(*p)) ++p;
     k = 0;
     while (isalnum(*p) && k < MAXTOK-1) name[k++] = *p++;
     if (k >= MAXTOK-1) {
          error(1, 0, "macro name too long");
     }
     name[k] = '\0';

     /* Get the args. */
     while (*p != '\0' && isspace(*p)) ++p;
     if (*p == '\0') {
          /* No args for this macro definition. */
          install(name, &evalst[a3]);
          return;
     }
     if (*p != '(') {
          error(1, 0, "'(' is expected");
     }
     k = 0;
     n = 0;
     for (;;) {
          while (*p != '\0' && !isalnum(*p)) ++p;
          if (*p == '\0') break;
          argptr[n++] = k;
          while (isalnum(*p))
               args[k++] = *p++;
          args[k++] = '\0';
          if (*p == '\0') break;
          while (*p != '\0' && *p != ',') ++p;
          if (*p == '\0') break;
     }
     
     /* Get the definition. */
     k = 0;
     l = 0;
     for (p = &evalst[a3]; ; ++p) {
          if (isalnum(*p)) {
               /* Collect a token. */
               token[l++] = *p;
          } else {
               token[l] = '\0';
               if (l > 0) {
                    /* Have collected a token. */
                    int m;
                    for (m = 0; m < n; m++)
                         if (strcmp(token, &args[argptr[m]]) == 0)
                              break;
                    if (m < n) {
                         /* This token is the (m+1)th arg. Convert it to
                          * "$m+1" */
                         char s[10]; /* enough to hold the arg number */
                         k += sprintf(s, "$%d", m+1);
                         strcat(defn, s);
                    } else {
                         /* Else not an arg. */
                         for (m = 0; m < l; m++)
                              defn[k++] = token[m];
                    }
                    l = 0;
               }
               if (*p == '\0') break;
               defn[k++] = *p;
          }
     }
     defn[k] = '\0';
     install(name, defn);
}

int main()
{
     char defn[MAXDEF], token[MAXTOK];
     const char *defname = "define";
     char deftype[2] = { DEFTYPE, '\0' };
     int t;
     int ap;                    /* first free position in argstack */
     int argstack[ARGSIZE];
     int callst[CALLSIZE];
     int nlb;
     int plev[CALLSIZE];
     
     install(defname, deftype);
     cp = -1;
     ap = 0;
     ep = 0;
     for (t = get_token(token, MAXTOK); t != EOF; t = get_token(token, MAXTOK)) {
          if (t == ALPHA) {
               if (lookup(token, defn) == 0) {
                    /* Undefined */
                    puttok(token);
               } else {         /* defined; put it in eval stack */
                    ++cp;
                    if (cp >= CALLSIZE)
                         error(1, 0, "call stack overflow");
                    callst[cp] = ap;
                    ap = push(ep, argstack, ap);
                    puttok(defn); /* push definition */
                    putchr('\0');
                    ap = push(ep, argstack, ap);
                    puttok(token); /* push name */
                    putchr('\0');
                    ap = push(ep, argstack, ap);
                    t = get_token(token, MAXTOK); /* peek at next */
                    ungetstr(token);
                    if (t != '(') { /* add () if not present */
                         ungetstr("()");
                    }
                    plev[cp] = 0;
               }
          } else if (t == '[') { /* strip one level of [] */
               nlb = 1;
               for (;;) {
                    t = get_token(token, MAXTOK);
                    if (t == '[')
                         nlb++;
                    else if (t == ']') {
                         nlb--;
                         if (nlb == 0)
                              break;
                    } else if (t == EOF) {
                         error(1, 0, "EOF in string");
                    }
                    puttok(token);
               }
          } else if (cp == -1) {
               /* Not in a macro at all */
               puttok(token);
          } else if (t == '(') {
               if (plev[cp] > 0) {
                    puttok(token);
               }
               ++plev[cp];
          } else if (t == ')') {
               --plev[cp];
               if (plev[cp] > 0) {
                    puttok(token);
               } else {         /* end of argument list */
                    putchr('\0');
                    eval(argstack, callst[cp], ap-1);
                    ap = callst[cp]; /* pop eval stack */
                    ep = argstack[ap];
                    --cp;
               }
          } else if (t == ',' && plev[cp] == 1) {
               /* New arg */
               putchr('\0');
               ap = push(ep, argstack, ap);
          } else {
               puttok(token);
          }
     }
     if (cp != -1)
          error(1, 0, "unexpected EOF.");
     return 0;
}

/* ------------------------------ */

/*
 * Table lookup.
 */

#define MAXPTR 100
#define MAXTBL 1000

int lastp;               /* last used position in nameptr */
int lastt;               /* last used position in table */
int nameptr[MAXPTR];
char table[MAXTBL];

/*
 * Look up name from the table.  Return 1 if found, or 0 if not.
 */
int lookup(const char *name, char def[MAXDEF])
{
     int i, j, k;

     for (i = lastp; i >= 0; i--) {
          j = nameptr[i];
          for (k = 0; name[k] == table[j] && name[k] != '\0'; k++) {
               j++;
          }
          if (name[k] == table[j]) {
               /* got one */
               strncpy(def, &table[j+1], MAXDEF);
               return 1;
          }
     }
     return 0;
}
               
void install(const char *name, const char *def)
{
     assert(name != NULL);
     assert(def != NULL);

     int name_len, def_len;

     name_len = strlen(name)+1; /* +1 for '\0' */
     def_len = strlen(def)+1;
     if (lastt+name_len+def_len > MAXTBL || lastp >= MAXPTR-1) {
          error(1, 0, "%s: too many definitions.", name);
     }
     lastp++;
     nameptr[lastp] = lastt+1;
     strcpy(&table[lastt+1], name);
     strcpy(&table[lastt+name_len+1], def);
     lastt += name_len+def_len;
}

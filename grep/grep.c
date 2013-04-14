/*
 * grep
 *   A regular expression parser, similar to UNIX grep. Just support
 *   ^, $, ., *, [], (), |, etc.
 *
 * Author: wbb
 * Date: 2010-03-02
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <stdarg.h>


int match_here(const char *regexp, const char *str, int *len);
int match_star(const char *begin, const char *end, 
        const char *regexp, const char *str, int *len);
int match_basic(const char *regexp, const char *str, int *len);
int match_param(const char *begin, const char *end, const char *str, int *len);
int match_bracket(const char *begin, const char *end, const char *str, int *len);
int match_paren(const char *begin, const char *regexp, const char *str, int *len);
void error(const char *fmt, ...);

/*
 * match --
 *   Search for regexp any where in str.
 *   Return 1 if found, 0 if not or -1 if syntax error on regexp.
 *   The position of substring in str is stored in first and the
 *   length of matched substring is stored in len.
 */
int match(const char *regexp, const char *str, int *first, int *len)
{
    assert(regexp && str);

    int r;
    if (regexp[0] == '^') {
        r = match_here(regexp+1, str, len);
        if (r > 0 && first)
            *first = 0;
        return r;
    }

    const char *save_str = str;     /* remember original str */
    do {
        if ((r = match_here(regexp, str, len))) {
            if (r > 0 && first)
                *first = str-save_str;
            return r;
        }
    } while (*str++ != '\0');
    return 0;
}


/*
 * match_here --
 *   Search for regexp at the beginning of str.
 */
int match_here(const char *regexp, const char *str, int *len)
{
    assert(regexp && str);
    
    int r;
    while (1) {
        if ((r = match_basic(regexp, str, len)))
            return r;

        /* 
         * Here means not matched.
         * Check if there is another alternative regexp.
         * Note '|' may be nested between '(' and ')'.
         */
        int depth = 0;
        while (*regexp != '\0') {
            if (depth == 0 && *regexp == '|')
                break;
            if (*regexp == '(')
                depth++;
            if (*regexp == ')')
                depth--;
            regexp++;
        }
        if (depth != 0) {
            error("'(' and ')' do not match");
            return -1;
        }
        if (*regexp == '|')
            regexp++;
        else
            return 0;
    }
    return 0;
}


/*
 * match_basic --
 *   Search for basic regexp (text, paren, bracket or star
 *   expressions) at the beginning of str.  A basic regexp is
 *   separated by '|' or terminated by '\0';
 */   
int match_basic(const char *regexp, const char *str, int *len)
{
    assert(regexp && str);

    int r, l = 0;

    while (1) {
        if (regexp[0] == '\0' || regexp[0] == '|' || regexp[0] == ')') {
            if (len)
                *len = l;
            return 1;
        }

        /* process '[' expressions */
        if (regexp[0] == '[') {
            /* search for the matched ']' */
            int i;
            for (i = 1; regexp[i] != '\0'; i++) {
                if (regexp[i] == ']')
                    break;
            }

            /* not found; error */
            if (regexp[i] == '\0') {
                error("'%c' does not have a match", regexp[0]);
                return -1;
            }

            if (regexp[i+1] == '*') { 
                r = match_star(regexp, regexp+i, regexp+i+2, str, len);
                *len += l;
                return r;
            } else {
                r = match_bracket(regexp, regexp+i, str, len);
            }
            if (r <= 0)
                return r;
            str += *len;
            regexp += i+1;
            l += *len;
            continue;
        }

        /* process '(' expressions */
        if (regexp[0] == '(') {
            /* search for the matched ')' */
            int i, depth = 0;
            for (i = 1; regexp[i] != '\0'; i++) {
                if (depth == 0 && regexp[i] == ')') {
                    if (regexp[i+1] == '*')
                        return match_star(regexp, regexp+i, regexp+i+2, str, len);
                    if (regexp[0] == '(')
                        r = match_paren(regexp, regexp+i, str, len);
                    if (r <= 0)
                        return r;
                    str += *len;
                    regexp += i+1;
                    l += *len;
                } else if (regexp[i] == '(')
                    depth++;
                else if (regexp[i] == ')')
                    depth--;
            }
            
            /* not found; error */
            if (regexp[i] == '\0') {
                error("'%c' does not have a match", regexp[0]);
                return -1;
            }
            continue;
        }    

        /* process text exrepssions */
        if (regexp[1] == '*')
            return match_star(regexp, regexp, regexp+2, str, len);
        if (regexp[0] == '$' && regexp[1] == '\0') {
            *len = l;
            return *str == '\0';
        }
        if (*str != '\0' && (regexp[0] == '.' || regexp[0] == *str)) {
            regexp++;
            str++;
            l++;
        } else
            return 0;
    }
    return 0;
}


/*
 * match_star --
 *   Search for star expression (param*regexp) at the beginning of str.
 *   'begin' and 'end' points to the beginning and end of star expression
 *   respectively and 'regexp' points to just beyond '*'.
 */
int match_star(const char *begin, const char *end, 
               const char *regexp, const char *str, int *len)
{
    assert(begin && end);
    assert((begin == end) ||
           (begin[0] == '[' && end[0] == ']') ||
           (begin[0] == '(' && end[0] == ')'));
    assert(regexp && str);

    int l, max, r, ismatch;

    ismatch = 0;
    max = 0;
    r = match_basic(regexp, str, &l);
    if (r < 0)
        return r;
    if (r > 0)
        ismatch = 1;
    if (r > 0 && max < l) {
        max = l;
    }

    /*
     * See if there is longer matched substring.
     */
    int l2 = 0, l3 = 0;
    l = 0;
    while (1) {
        r = match_param(begin, end, str, &l);
        if (r < 0)
            return r;
        if (r == 0) {
            if (len)
                *len = max;
            return ismatch;
        }

        str += l;
        l3 += l;
        r = match_basic(regexp, str, &l2);
        if (r < 0)
            return r;
        else if (r > 0) {
            ismatch = 1;
            if (max < l3 + l2)
                max = l3 + l2;
        }
    }
    return 0;
}

/*
 * match_param --
 *   Helpful function for match_star.
 *   Between begin and end is a text, bracket or paren expression.
 *   Return 1 if matched. The length of matched substring is stored in
 *   len.
 */
int match_param(const char *begin, const char *end, const char *str, int *len)
{
    assert(begin && end);
    assert((begin == end) ||
           (begin[0] == '[' && end[0] == ']') ||
           (begin[0] == '(' && end[0] == ')'));
    assert(str);

    int r;

    if (begin[0] == '[')
        r = match_bracket(begin, end, str, len);
    else if (begin[0] == '(')
        r = match_paren(begin, end, str, len);
    else if (str[0] != '\0' && (begin[0] == '.' || begin[0] == str[0])) {
        r = 1;
        *len = 1;
    } else
        r = 0;
    return r;
}


/*
 * match_bracket --
 *   Search for bracket expression ([abc], [a-d], etc) at the beginning of
 *   str.  'begin' and 'end' point to '[' and ']' respectively.
 *   Return 1 if matched, 0 if not matched or < 0 on error.
 */
int match_bracket(const char *begin, const char *end, const char *str, int *len)
{
    assert(begin && begin[0] == '[');
    assert(end && end[0] == ']');
    assert(str);

    char buf[BUFSIZ];

    /* collect the char between '[' and ']' */
    int i = 1, j = 0;
    while (begin[i] != ']') {
        if (begin[i] != '-') {
            buf[j++] = begin[i++];
        } else {
            i++;
            if (begin[i] == '-' || begin[i] < begin[i-2]) {
                error("error between '[' and ']' around '-'");
                return -1;
            }
            while (buf[j-1] < begin[i]) {
                buf[j] = buf[j-1] + 1;
                j++;
            }
            i++;
        }
    }
    buf[j] = '\0';

    /* check if str[0] matches one char of buf */
    for (int i = 0; buf[i] != '\0'; i++)
        if (buf[i] == str[0]) {
            if (len)
                *len = 1;
            return 1;
        }
    return 0;
}

/*
 * match_paren --
 *   Search for paren expression ((ab|cd), etc) at the beginning of
 *   str.  'begin' and 'end' points to '(' and ')' respectively.
 *   Return 1 if matched, 0 if not matched or <0 on error.
 */
int match_paren(const char *begin, const char *end, const char *str, int *len)
{
    assert(begin && end && str);
    assert(begin[0] == '(' && end[0] == ')');

    int r;
    const char *regexp;

    regexp = begin+1;
    while (1) {
        if ((r = match_basic(regexp, str, len)))
            return r;

        /*
         * Reaching here means not matched.
         * Check next alternative regexp.
         * Note '|' may be nested in another pair of '(' and ')',
         * so we introduce depth.
         */
        int depth = 0;
        while (*regexp != '\0') {
            if (depth == 0 && (*regexp == '|' || *regexp == ')'))
                break;
            if (*regexp == '(')
                depth++;
            if (*regexp == ')')
                depth--;
            regexp++;
        }
        if (depth != 0) {
            error("'(' and ')' do not match");
            return -1;
        }
        if (*regexp == ')')  /* no alternative */
            return 0;
        else
            regexp++;
    } 
    return 0;
}

void error(const char *fmt, ...)
{
    assert(fmt);

    va_list ap;

    fputs("regexp error: ", stderr);
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    fputs("\n", stderr);
}

struct case_tag {
    const char *regexp, *str;
    int idx, len;
} testcase[] = {
    { "^$", "", 0, 0 },
    { "^$", "ab", -1, 0 },
    { "^a", "ab", 0, 1 },
    { "^a", "ba", -1, 0 },
    { "a$", "ba", 1, 1 },
    { "^.*", "ba", 0, 2 },
    { "^a*", "aaaa", 0, 4 },
    { "a*a*", "aaa", 0, 3 },
    { "a*", "aaad", 0, 3 },
    { "a*d", "aaae", -1, 0 },
    { "a*d", "aaad", 0, 4 },
    { "[a-d]", "efabc", 2, 1 },
    { "[a-d][a-d]*", "efabc", 2, 3 },
    { "[a-d][a-d]*", "efabce", 2, 3 }
};

void test(void)
{
    int i, ntests, nsuccess;

    ntests = 0;
    nsuccess = 0;
    for (i = 0; (unsigned) i < sizeof testcase / sizeof(struct case_tag); i++) {
        int first, len, r;
        r = match(testcase[i].regexp, testcase[i].str, &first, &len);
        ntests++;
        if ((r == 0 && testcase[i].idx == -1) ||
            (r > 0 && testcase[i].idx == first && testcase[i].len == len)) {
            nsuccess++;
        } else {
            printf("fail: regexp: %s, string: %s, "
                   "%d, %d, but expect %d, %d\n",
                    testcase[i].regexp, testcase[i].str, testcase[i].idx, 
                    testcase[i].len, first, len);
        }
    }
    /* printf("------------- statistics -------------\n"); */
    /* printf("#success/#tests: %d/%d\n", nsuccess, ntests); */
}

int main()
{
    test();
    return 0;
}

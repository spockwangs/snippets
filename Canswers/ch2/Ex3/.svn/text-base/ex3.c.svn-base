/*************************************************************************
 * K&R Exercise 2-3
 *      Write the function htoi(s), which converts a string of hexadecimal
 *      digits (including an optional 0x or 0X) into its equivalent
 *      integer value. The allowable digits are 0 through 9, a through f,
 *      and A through F.
 *
 */

#include <stdio.h>
#include <ctype.h>
#include <assert.h>

int hex2dec(char c);
int htoi(char s[], unsigned *pn);

int main()
{
    char str[100];
    unsigned n;
    int ret;

    printf("Please input a hexdecimal integer: ");
    scanf("%s", str);
    ret = htoi(str, &n);
    if (ret == -1)
        fprintf(stderr, "error: format of string '%s' is wrong!\n",
                str);
    else if (ret == -2)
        fprintf(stderr, "error: '%s' overflow!\n", str);
    else
        printf("Its decimal version is %u.\n", n);

    return 0;
}

/****************************************************************
 * htoi - convert a hexdecimal integer to a decimal integer
 *
 * Parameters:
 *      s[]: null-terminated string of hexdecimal digits
 *      pn:  pointer to a unsigend int where converted integer is
 *           stored.
 * Returns:
 *      Returns 0 if successful, -1 if format is wrong and -2 if
 *      overflow.
 */
int htoi(char s[], unsigned *pn)
{
    int i, j, t; 
    unsigned m, n;
    char *p;

    /* calculate how many bits a unsigend int has in this machine */
    i = 1;
    for (j = 1; i > 0; j++)
        i <<= 1;

    i = 0;
    if (s[i] == '0') {
        i++;
        if (s[i] == 'x' || s[i] == 'X') {
            i++;
        } else {
            return -1;
        }
    }
    n = 0;
    p = &s[i];
    i = 0;
    while (p[i] != '\0') {
        t = hex2dec(p[i]);
        if (t == -1) 
            return -1;
        n = (n<<4) + t;
        i++;
    }
    if (i*4 > j) {  /* overflow */
        return -2;
    }
    sscanf(s, "%x", &m);
    assert(m == n);
    *pn = n;
    return 0;
}

/* hex2dec - convert a hex char to decimal integer 
 * NOTE: this program is not limited in ASCII characters.
 */
int hex2dec(char c)
{
    char str[] = "0123456789ABCDEF";
    int i;

    for (i = 0; str[i] != '\0'; i++)
        if (str[i] == toupper(c))
            return i;
    return -1;
}

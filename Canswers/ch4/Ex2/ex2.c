/************************************************************************
 * K&R Exercise 4-2
 *     Extend atof to handle scientific notation of the form
 *     123.45e-6
 *     where a floating-point number may be followed by e or E and an
 *     optionally signed exponent.
 */

#include <stdio.h>
#include <ctype.h>

double atof(char s[])
{
    double val, power;
    int i, sign, sign2, m;

    for (i = 0; isspace(s[i]); i++)
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (val = 0.0; isdigit(s[i]); i++) {
        val = 10.0 * val + s[i] - '0';
    }
    if (s[i] == '.')
        i++;
    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + s[i] - '0';
        power *= 10.0;
    }
    val = sign * val / power;
    if (s[i] == 'e' || s[i] == 'E')
        i++;
    sign2 = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (m = 0; isdigit(s[i]); i++) {
        m = 10 * m + s[i] - '0';
    }
    power = 1;
    if (sign2 > 0) {
        while (m > 0) {
            power *= 10.0;
            m--;
        }
    } else {
        while (m > 0) {
            power /= 10.0;
            m--;
        }
    }
    return val * power;
}

int main()
{
    struct TEST {
        double f;
        char *s;
    } test[] = {
        { 0.0, "0.0" }, 
        { 1.0, "1.0" },
        { 1.1, "1.1" },
        { 123.45, "123.45" },
        { 123.45e2, "123.45e+2" }, 
        { 123.45e-2, "123.45e-2" },
        { 123456e5, "123456e+5" },
        { 123456e-5, "123456e-5" },
    };
    int i;
    double f;
    int success, failure, total;

    success = failure = total = 0;
    for (i = 0; i < sizeof(test)/sizeof(struct TEST); i++) {
        total++;
        f = atof(test[i].s);
        if (f == test[i].f)
            success++;
        else {
            printf("Fail: %.20f, expected %.20f\n",
                    f, test[i].f);
            failure++;
        }
    }
    printf("Total tests: %d, #successes: %d, #failures: %d\n",
            total, success, failure);
    return 0;
}

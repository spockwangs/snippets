#include "minicrt.h"

char *itoa(int n, char *str, int radix)
{
     const char *digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
     char *p = str;
     char *head = str;

     if (p == NULL || radix < 2 || radix > 36)
          return p;
     if (radix != 10 && n < 0)
          return p;

     if (n == 0) {
          *p++ = '0';
          *p = 0;
          return p;
     }
     if (radix == 10 && n < 0) {
          *p++ = '-';
          n = -n;
     }
     while (n) {
          *p++ = digits[n%radix];
          n /= radix;
     }
     *p = 0;
     for (--p; head < p; ++head, --p) {
          char tmp = *head;
          *head = *p;
          *p = tmp;
     }
     return str;
}

int strcmp(const char *s1, const char *s2)
{
     while ((*s1 == *s2) && (*s1 != 0)) {
          ++s1;
          ++s2;
     }

     if (*s1 == 0)
          return -1;
     else if (*s2 == 0)
          return 1;
     return *s1 - *s2;
}

char *strcpy(char *dest, const char *src)
{
     char *r = dest;
     while (*src)
          *dest++ = *src++;
     *dest = 0;
     return r;
}

unsigned strlen(const char *s)
{
     unsigned int n = 0;
     if (s == NULL)
          return 0;
     for (; *s != '\0'; ++s)
          ++n;
     return n;
}

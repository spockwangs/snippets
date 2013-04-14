/*
 * From "More Programming Pearls" column 1.
 *
 * Print primes less than 1000.
 */

#include <stdio.h>

/*
 * Return 1 if 'n' is a prime, or 0 if not.
 */
int prime(int n)
{
     int i;

     /* test all integers between 2 and n-1 to see whether they divide n */
     for (i = 2; i < n; i++) {
          if (n % i == 0)
               return 0;
     }
     return 1;
}

int main()
{
     int i, n;
     n = 1000;
     for (i = 2; i <= n; i++) {
          if (prime(i))
               printf("%d\n", i);
     }

     return 0;
}
     

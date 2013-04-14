/*
 * Copyright (c) 2010. Wang Bingbing.
 * 
 * Author: 王兵兵 (wbbtiger@gmail.com)
 * Date: 2010-10-09
 *
 * 打印一个螺旋矩阵. 
 */

#include <stdio.h>

int min(int a, int b)
{
     return a < b ? a : b;
}

int matrix(int i, int j, int n)
{
     int m, a, l;

     m = min(min(i, n-1-i), min(j, n-1-j));
     i -= m;
     j -= m;
     a = 1 + 4*m*(n-m);
     l = n - 2*m;
     if (i == 0)
          return a+j;
     else if (j == 0)
          return a + 4*(l-1) - i;
     else if (i == l-1)
          return a + 4*l - 3 - l - j;
     /* else j == m-1 */
     return a + l-1 + i;
}

int main(int argc, char *argv[])
{
     int i, j, n;

     if (argc != 2) {
          fprintf(stderr, "Usage: %s number\n", argv[0]);
          return 1;
     }
     n = atoi(argv[1]);
     for (i = 0; i < n; i++)
          for (j = 0; j < n; j++)
               printf("%3d%c", matrix(i, j, n), j == n-1 ? '\n' : ' ');
     return 0;
}
     

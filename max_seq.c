/*
 * Copyright (c) 2010. Wang Bingbing.
 *
 * Calculate max length of consecutive substring in a text without
 * repeating characters.  This is a test problem of Jinshan Corporation.
 *
 * who: 王兵兵 (wbbtiger@gmail.com)
 * when: 2010-10-01 17:39:21
 */
 
#include <stdio.h>

int max(int a, int b)
{
     return a < b ? b : a;
}

/*
 * Return max length of consecutive substring in 'text' without repeating
 * characters.  Assume that there are only lowercase letters in 'text'.
 */
int search(const char *text)
{
     int max_len = 0, len = 0;
     int pos[26];               /* hold position of last char c in pos[c] */
     int i;

     for (i = 0; i < 26; i++)
          pos[i] = -1;

     for (i = 0; text[i] != '\0'; i++) {
          if (pos[text[i]-'a'] == -1 ||
              pos[text[i]-'a'] < i-len) {
               pos[text[i]-'a'] = i;
               len++;
          } else {
               max_len = max(max_len, len);
               len = i - pos[text[i]-'a'];
               pos[text[i]-'a'] = i;
          }
     }
     max_len = max(max_len, len);
     return max_len;
}

int main()
{
     char str[100];
     while (scanf("%s", str) == 1)
          printf("max = %d\n", search(str));
     return 0;
}

/* 
 * date.c -- Show current date and time like date(1).
 *
 * $Id: date.c 54 2011-08-26 16:44:38Z  $
 */

#include <stdio.h>
#include <locale.h>
#include <time.h>
#include <errno.h>
#include <error.h>
#include <stdlib.h>

int main()
{
    time_t t = time(NULL);
    if (t == (time_t) -1)
        error(EXIT_FAILURE, errno, "time");
    struct tm *tmptr = localtime(&t);
    wchar_t ws[100];

    /* 
     * Set current LC_TIME.  The formatting of wcsftime is according
     * to LC_TIME.
     */
    if (setlocale(LC_TIME, "") == NULL)
        error_at_line(EXIT_FAILURE, errno, __FILE__, __LINE__, "setlocale");
    if (wcsftime(ws, sizeof(ws), L"%a %b %d %T %Z %Y", tmptr) == 0)
        error(EXIT_FAILURE, errno, "wcsftime");

    /* 
     * Set current LC_CTYPE so we can print the string correctly.
     */
    if (setlocale(LC_CTYPE, "") == NULL)
        error_at_line(EXIT_FAILURE, errno, __FILE__, __LINE__, "setlocale");
    printf("%ls\n", ws);
    return EXIT_SUCCESS;
}

#include <stdio.h>

olddef(l)
long l;
{
    printf("olddef: l = %ld\n", l);
    return 0;
}

int main()
{
    int l = 1;
    olddef(l);

    return 0;
}


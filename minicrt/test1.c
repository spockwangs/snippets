#include "minicrt.h"

int main(int argc, char *argv[])
{
     int i;

     for (i = 0; i < argc; i++)
          fprintf(stdin, "%s\n", argv[i]);
     return 0;
}
     

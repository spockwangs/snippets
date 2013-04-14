/*
 * entry.c
 */

extern int main(int argc, char *argv[]);
extern void exit(int);

void entry(void)
{
     int ret = 0;
     int argc;
     char **argv;
     char *ebp = 0;
     asm("movl %%ebp,%0\n":"=r"(ebp));

     argc = *(int *)(ebp+4);
     argv = (char **)(ebp+8);

     if (heap_init() < 0)
          exit(1);
     if (io_init() < 0)
          exit(1);

     do_global_ctors();
     
     ret = main(argc, argv);
     exit(ret);
}

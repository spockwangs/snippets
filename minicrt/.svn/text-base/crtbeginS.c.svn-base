typedef void (*ctor_fun)(void);

ctor_fun CTOR_BEGIN[1] __attribute__ ((section(".ctors"))) =
{ (ctor_fun) -1 };

void do_global_ctors()
{
    const ctor_fun *p = CTOR_BEGIN;
    ++p;
    while (*(int *)p != -1) {
        (**p)();
        ++p;
    }
}

void _init() __attribute__ ((section(".init"))
     {
          do_global_ctors();

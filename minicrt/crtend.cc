typedef void (*ctor_fun)(void);

ctor_fun CTOR_END[1] __attribute__ ((section(".ctors"))) = { (ctor_fun) -1 };

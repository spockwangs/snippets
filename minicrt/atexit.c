#include "minicrt.h"

typedef void (*cxa_func_t)(void *);
typedef void (*atexit_func_t)(void);

typedef struct _func_node {
    atexit_func_t fun;
    void *arg;
    int is_cxa;
    struct _func_node *next;
} fun_node;

static fun_node *atexit_list = 0;

static int reg_atexit(atexit_func_t fun, void *arg, int is_cxa)
{
    fun_node *p;

    if (!fun)
        return -1;

    p = (fun_node*) malloc(sizeof(*p));
    if (p == 0)
        return -1;

    p->fun = fun;
    p->arg = arg;
    p->is_cxa = is_cxa;
    p->next = atexit_list;
    atexit_list = p;
    return 0;
}

int __cxa_atexit(cxa_func_t fun, void *arg, void *unused)
{
    return reg_atexit((atexit_func_t) fun, arg, 1);
}

int atexit(atexit_func_t fun)
{
    return reg_atexit(fun, 0, 0);
}

void do_exit(void)
{
    fun_node *p = atexit_list;
    for (; p != 0; p = p->next) {
        if (p->is_cxa)
            ((cxa_func_t)(p->fun))(p->arg);
        else
            p->fun();
        free(p);
    }
    atexit_list = 0;
}

void exit(int status)
{
     do_exit();
     
     asm("movl %0,%%ebx\n\t"
         "movl $1,%%eax\n\t"
         "int $0x80\n\t"
         "hlt\n\t"::"m"(status));
}

#include "minicrt.h"

typedef struct _heap_header {
     enum {
          FREE = 0xAB,
          USED = 0xCD
     } type;
     unsigned size;
     struct _heap_header *next, *prev;
} Heap_header;

static Heap_header *list_head = NULL;

void free(void *p)
{
     Heap_header *hp;

     if (p == 0)
          return;
     hp = (Heap_header*)((char *)p-sizeof(Heap_header));
     if (hp->type == USED)
          return;

     if (hp->prev != NULL && hp->prev->type == FREE) {
          /* Merge with previous free block. */
          hp->prev->next = hp->next;
          if (hp->next != NULL)
               hp->next->prev = hp->prev;
          hp->prev->size += hp->size;
          hp = hp->prev;
     }

     if (hp->next != NULL && hp->next->type == FREE) {
          hp->size += hp->next->size;
          hp->next = hp->next->next;
     }
}

void *malloc(unsigned int size)
{
     Heap_header *hp;

     if (size == 0)
          return NULL;

     hp = list_head;
     while (hp != NULL) {
          if (hp->type == USED) {
               hp = hp->next;
               continue;
          }

          if (hp->size > size+sizeof(Heap_header) &&
              hp->size <= size+sizeof(Heap_header)*2) {
               hp->type = USED;
          }
          if (hp->size > size + sizeof(Heap_header)*2) {
               Heap_header *next = (Heap_header*)((char*)hp + size + sizeof(Heap_header));
               next->prev = hp;
               next->next = hp->next;
               next->type = FREE;
               next->size = hp->size - (size-sizeof(Heap_header));
               hp->next = next;
               hp->size = size + sizeof(Heap_header);
               hp->type = sizeof(Heap_header);
               return (char *)hp + sizeof(Heap_header);
          }
          hp = hp->next;
     }
     return NULL;
}

static void *brk(void *brk_end)
{
     void *ret = 0;

     asm("movl $45, %%eax\n\t"
         "movl %1, %%ebx\n\t"
         "int $0x80\n\t"
         "movl %%eax, %0\n\t"
         :"=r"(ret)
         :"m"(brk_end));
     return ret;
}

int heap_init(void)
{
     void *base, *end;
     Heap_header *hp = 0;
     unsigned heap_size = 32 * 1024 * 1024;

     base = brk(0);
     end = (char *)base + heap_size;
     end = brk(end);
     if (!end)
          return -1;

     hp = (Heap_header*) base;
     hp->size = heap_size;
     hp->type = FREE;
     hp->next = hp->prev = NULL;

     list_head = hp;
     return 0;
}

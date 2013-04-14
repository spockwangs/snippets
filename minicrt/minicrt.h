#ifndef __MINICRT_H
#define __MINICRT_H

#ifdef __cplusplus
extern "C" {
#endif
     
     typedef int FILE;

#define EOF (-1)
#define NULL 0

     void free(void *p);
     void *malloc(unsigned size);
     int heap_init();

     char *itoa(int n, char *str, int radix);
     int strcmp(const char *src, const char *dest);
     char *strcpy(char *dest, const char *src);
     unsigned strlen(const char *str);

#define stdin ((FILE*)0)
#define stdout ((FILE*)1)
#define stderr ((FILE*)2)

     int io_init();
     FILE *fopen(const char *path, const char *mode);
     int fread(void *buf, int size, int c, FILE *fp);
     int fwrite(const void *buf, int size, int c, FILE *fp);
     int fclose(FILE *fp);
     int fseek(FILE *fp, int offset, int set);

     int fputc(int c, FILE *fp);
     int fputs(const char *str, FILE *fp);
     int printf(const char *fmt, ...);
     int fprintf(FILE *fp, const char *fmt, ...);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

void *operator new(unsigned int size);
void *operator new[](unsigned int size);
void operator delete(void *p);
void operator delete[](void *p);

int atexit(void (*atexit_fun_t)(void));
void do_exit(void);
#endif /* __cplusplus */

#endif /* __MINICRT_H */

#include "minicrt.h"

int io_init(void)
{
     return 0;
}

static int open(const char *path, int flags, int mode)
{
     int fd = 0;
     asm("movl $5, %%eax\n\t"
         "movl %1, %%ebx\n\t"
         "movl %2, %%ecx\n\t"
         "movl %3, %%edx\n\t"
         "int $0x80\n\t"
         "movl %%eax, %0\n\t"
         :"=m"(fd)
         :"m"(path),"m"(flags),"m"(mode));
     return fd;
}

static int read(int fd, void *buf, unsigned size)
{
     int ret = 0;
     asm("movl $3, %%eax\n\t"
         "movl %1, %%ebx\n\t"
         "movl %2, %%ecx\n\t"
         "movl %3, %%edx\n\t"
         "int $0x80\n\t"
         "movl %%eax, %0\n\t"
         :"=m"(ret)
         :"m"(fd),"m"(buf),"m"(size));
     return ret;
}

static int write(int fd, const void *buf, unsigned size)
{
     int ret = 0;
     asm("movl $4, %%eax\n\t"
         "movl %1, %%ebx\n\t"
         "movl %2, %%ecx\n\t"
         "movl %3, %%edx\n\t"
         "int $0x80\n\t"
         "movl %%eax, %0\n\t"
         :"=m"(ret)
         :"m"(fd),"m"(buf),"m"(size));
     return ret;
}

static int close(int fd)
{
     int ret = 0;
     asm("movl $6, %%eax\n\t"
         "movl %1, %%ebx\n\t"
         "int $0x80\n\t"
         "movl %%eax, %0\n\t"
         :"=m"(ret)
         :"m"(fd));
     return ret;
}

static int seek(int fd, int offset, int mode)
{
     int ret = 0;
     asm("movl $19, %%eax\n\t"
         "movl %1, %%ebx\n\t"
         "movl %2, %%ecx\n\t"
         "movl %3, %%edx\n\t"
         "int $0x80\n\t"
         "movl %%eax, %0\n\t"
         :"=m"(ret)
         :"m"(fd),"m"(offset),"m"(mode));
     return ret;
}

FILE *fopen(const char *filename, const char *mode)
{
     int fd, flags, access;

     flags = 0;
     access = 0700;

#define O_RDONLY 00
#define O_WRONLY 01
#define O_RDWR 02
#define O_CREAT 0100
#define O_TRUNC 01000
#define O_APPEND 02000

     if (strcmp(mode, "w") == 0)
          flags |= O_WRONLY | O_CREAT | O_TRUNC;
     if (strcmp(mode, "w+") == 0)
          flags |= O_RDWR | O_CREAT | O_TRUNC;
     if (strcmp(mode, "r") == 0)
          flags |= O_RDONLY;
     if (strcmp(mode, "r+") == 0)
          flags |= O_RDWR | O_CREAT;

     fd = open(filename, flags, access);
     return (FILE *)fd;
}

int fread(void *buf, int size, int c, FILE *fp)
{
     return read((int)fp, buf, size * c);
}

int fwrite(const void *buf, int size, int c, FILE *fp)
{
     return write((int)fp, buf, size * c);
}

int fclose(FILE *fp)
{
     return close((int)fp);
}

int fseek(FILE *fp, int offset, int set)
{
     return seek((int)fp, offset, set);
}
     

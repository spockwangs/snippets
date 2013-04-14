#include "minicrt.h"

int fputc(int c, FILE *fp)
{
     if (fwrite(&c, 1, 1, fp) != 1)
          return EOF;
     else
          return c;
}

int fputs(const char *s, FILE *fp)
{
     int len = strlen(s);
     if (fwrite(s, 1, len, fp) != len)
          return EOF;
     else
          return len;
}

typedef char* va_list;
#define va_start(ap, arg) (ap = (va_list)&arg+sizeof(arg))
#define va_arg(ap, t) (*(t*)(ap += sizeof(t), ap-sizeof(t)))
#define va_end(ap) ((ap) = (va_list)0)

int vfprintf(FILE *fp, const char *fmt, va_list ap)
{
     int ret = 0;
     char buf[20];
     const char *p;
     int is_conv = 0;
     
     for (p = fmt; *p != 0; ++p) {
          if (!is_conv) {
               if (*p == '%')
                    is_conv = 1;
               else if (fputc(*p, fp) < 0)
                    return EOF;
               else
                    ret++;
               continue;
          }

          /* Do convertion. */
          switch (*p) {
          case '%':
               if (fputc('%', fp) < 0)
                    return EOF;
               ++ret;
               break;
          case 'd':
               itoa(va_arg(ap, int), buf, 10);
               if (fputs(buf, fp) < 0)
                    return EOF;
               ret += strlen(buf);
               break;
          case 's': {
               const char *s = va_arg(ap, const char *);
               if (fputs(s, fp) < 0)
                    return EOF;
               ret += strlen(s);
               break;
          }
          default:
               if (fputc(*p, fp) < 0)
                    return EOF;
               else
                    ++ret;
               break;
          }
          is_conv = 0;
     }
     return ret;
}

int printf(const char *fmt, ...)
{
     va_list ap;
     va_start(ap, fmt);
     return vfprintf(stdout, fmt, ap);
}

int fprintf(FILE *fp, const char *fmt, ...)
{
     va_list ap;
     va_start(ap, fmt);
     return vfprintf(fp, fmt, ap);
}


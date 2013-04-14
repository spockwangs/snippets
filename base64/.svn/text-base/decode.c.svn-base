#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <error.h>

#define NDEBUG 1

/*
 * 0xFF is error
 * 0xFE is ignored
 */
#define B64_ERROR       	0xFF
#define B64_IGNORE              0xFE

static const unsigned char ascii2bin[128]={
     0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
     0xFF,0xFE,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,
     0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
     0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
     0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
     0xFF,0xFF,0xFF,0x3E,0xFF,0xFF,0xFF,0x3F,
     0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,
     0x3C,0x3D,0xFF,0xFF,0xFF,0x00,0xFF,0xFF,
     0xFF,0x00,0x01,0x02,0x03,0x04,0x05,0x06,
     0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,
     0x0F,0x10,0x11,0x12,0x13,0x14,0x15,0x16,
     0x17,0x18,0x19,0xFF,0xFF,0xFF,0xFF,0xFF,
     0xFF,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,0x20,
     0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,
     0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,0x30,
     0x31,0x32,0x33,0xFF,0xFF,0xFF,0xFF,0xFF,
};

typedef struct decode_ctx {
     int number;
     int length;
     unsigned char data[80];
     int eof;                   /* have we seen '='? */
} DECODE_CTX;

int decode_block(unsigned char *to, const unsigned char *from, int len);

void decode_init(DECODE_CTX *ctx)
{
     ctx->number = 0;
     ctx->length = 64;
     ctx->eof = 0;
}

/*
 * 0 end of file
 * -1 error
 * >0 #bytes output
 */
int decode_update(DECODE_CTX *ctx, unsigned char *out, int *outl,
                  const unsigned char *in, int inl)
{
     int r, n, i;
     unsigned char *d;
     int total = 0;
     
     r = 1;
     n = ctx->number;
     d = ctx->data;

     if (inl == 0) {
          r = 0;
          goto end;
     }
		
     /* We parse the input data */
     for (i = 0; i < inl; i++) {
          int tmp;
          int eof = 0;

          tmp = *(in++);
          int v = ascii2bin[tmp];

          /* only save the good data :-) */
          switch (v) {
          case B64_ERROR:
               r = -1;
               goto end;
          case B64_IGNORE:
               continue;
          default:
               assert(n <= ctx->length);
               d[n++]=tmp;
               break;
          }
          
          if (ctx->eof == 1) {
               if (tmp != '=') {
                    r = -1;
                    goto end;
               } else {
                    ctx->eof++;
                    eof = 1;
               }
          } else if (tmp == '=') {
               int residue = (n-1)%4;
               if (residue != 2 && residue != 3) {
                    r = -1;
                    goto end;
               }
               if (residue == 3) {
                    eof = 1;
               }
               ctx->eof++;
          }

          if (eof || n >= ctx->length) {
               int t = decode_block(out, d, n);
               if (t < 0) {
                    r = -1;
                    goto end;
               }
               total += t - ctx->eof;
               ctx->eof = 0;
               out += t;
               n = 0;
          }
          if (eof)
               break;
     }
end:
     *outl = total;
     ctx->number = n;
     if (r < 0)
          return r;
     return total;
}

int decode_block(unsigned char *to, const unsigned char *from, int len)
{
     int a, b, c, d, i;
     unsigned long l;
     int ret;

     ret = 0;
     if (len%4 != 0)
          return -1;
     for (i=0; i < len; i+=4) {
          a = ascii2bin[*(from++)];
          b = ascii2bin[*(from++)];
          c = ascii2bin[*(from++)];
          d = ascii2bin[*(from++)];
          if ((a & 0x80) || (b & 0x80) ||
              (c & 0x80) || (d & 0x80))
               return(-1);
          l = ((((unsigned long)a)<<18L)|
               (((unsigned long)b)<<12L)|
               (((unsigned long)c)<< 6L)|
               (((unsigned long)d)     ));
          *(to++)=(unsigned char)(l>>16L)&0xff;
          *(to++)=(unsigned char)(l>> 8L)&0xff;
          *(to++)=(unsigned char)(l     )&0xff;
          ret+=3;
     }
     return(ret);
}

int decode_final(DECODE_CTX *ctx, unsigned char *out, int *outlen)
{
     int r;

     if (ctx->number > 0) {
          r = decode_block(out, ctx->data, ctx->number);
          if (r < 0)
               return -1;
          ctx->number = 0;
          *outlen = r;
     } else
          *outlen = 0;
     return 0;
}

int main()
{
     static unsigned char input[4098], output[3074];
     int outlen, n;
     DECODE_CTX ctx;

     decode_init(&ctx);
     while ((n = fread(input, 1, sizeof input, stdin)) > 0) {
          int r = decode_update(&ctx, output, &outlen, input, n);
          if (r == -1) {
               error(1, 0, "error in input\n");
          }
          fwrite(output, outlen, 1, stdout);
          if (r == 0)
               break;
     }
     if (decode_final(&ctx, output, &outlen) < 0)
          error(1, 0, "error in input\n");
     fwrite(output, outlen, 1, stdout);
     return 0;
}
                    
                    

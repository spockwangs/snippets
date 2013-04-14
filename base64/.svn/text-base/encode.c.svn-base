/*
 * encode.c -- Base64 encoder
 *
 * Time-stamp: <2010-08-06 13:36:13 wbb>
 */

#include <error.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

#define NDEBUG 1

int encode_block(unsigned char *to, const unsigned char *from, int len);

static const unsigned char bin2ascii[65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
     "abcdefghijklmnopqrstuvwxyz0123456789+/";

typedef struct encode_ctx {
     int number;
     int length;
     unsigned char data[80];
} ENCODE_CTX;

void encode_init(ENCODE_CTX *ctx)
{
     ctx->number = 0;
     ctx->length = 48;
}

void encode_update(ENCODE_CTX *ctx, const unsigned char *in, int inlen,
                   unsigned char *out, int *outlen)
{
     int i, j;
     unsigned int total=0;

     *outlen = 0;
     if (inlen == 0)
          return;
     assert(ctx->length <= (int)sizeof(ctx->data));
     if ((ctx->number + inlen) < ctx->length) {
          memcpy(&(ctx->data[ctx->number]), in, inlen);
          ctx->number += inlen;
          return;
     }
     if (ctx->number != 0) {
          i = ctx->length - ctx->number;
          memcpy(&(ctx->data[ctx->number]), in, i);
          in += i;
          inlen -= i;
          j = encode_block(out, ctx->data, ctx->length);
          ctx->number = 0;
          out += j;
          *(out++)='\n';
          *out='\0';
          total=j+1;
     }
     while (inlen >= ctx->length) {
          j = encode_block(out, in, ctx->length);
          in += ctx->length;
          inlen -= ctx->length;
          out += j;
          *(out++) = '\n';
          *out='\0';
          total += j+1;
     }
     if (inlen != 0)
          memcpy(&(ctx->data[0]), in, inlen);
     ctx->number = inlen;
     *outlen = total;
}

int encode_block(unsigned char *to, const unsigned char *from, int len)
{
     int i, ret = 0;
     unsigned long l;

     for (i = len; i > 0; i -= 3) {
          if (i >= 3) {
               l = ((unsigned long) from[0] << 16) |
                    ((unsigned long) from[1] << 8) |
                    from[2];
               *to++ = bin2ascii[(l>>18)&0x3F];
               *to++ = bin2ascii[(l>>12)&0x3F];
               *to++ = bin2ascii[(l>>6)&0x3F];
               *to++ = bin2ascii[l&0x3F];
          } else {
               l = ((unsigned long)from[0]) << 16L;
               if (i == 2)
                    l |= ((unsigned long)from[1]<<8L);

               *to++ = bin2ascii[(l>>18)&0x3F];
               *to++ = bin2ascii[(l>>12)&0x3F];
               *to++ = (i==1) ? '=' : bin2ascii[(l>>6)&0x3F];
               *to++ = '=';
          }
          ret += 4;
          from += 3;
     }
     *to = '\n';
     return ret;
}

void encode_final(ENCODE_CTX *ctx, unsigned char *out, int *outlen)
{
     int r = 0;

     if (ctx->number > 0) {
          r = encode_block(out, ctx->data, ctx->number);
          out[r++] = '\n';
          out[r] = '\0';
          ctx->number = 0;
     }
     *outlen = r;
}

int main()
{
     static unsigned char input[1024], output[1400];
     int inlen, outlen;
     ENCODE_CTX ctx;

     encode_init(&ctx);
     while ((inlen = fread(input, 1, sizeof input, stdin)) > 0) {
          encode_update(&ctx, input, inlen, output, &outlen);
          fwrite(output, outlen, 1, stdout);
     }
     encode_final(&ctx, output, &outlen);
     fwrite(output, outlen, 1, stdout);
     return 0;
}

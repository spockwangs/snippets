/*
 * md5.h
 *
 * Tipical use
 *   unsigned char digest[16];
 *   MD5_CTX context;
 *   MD5Init(&context);
 *   MD5Update(&context, input, inputlen);
 *   MD5Final(digest, &context);
 *   // Then digest[16] contains the MD5 sum.
 */

 #ifndef __MD5_H
# define __MD5_H

#include <stdint.h>

/* MD5 context. */
typedef struct {
    uint32_t state[4];             /* state (ABCD) */
    uint32_t count[2];             /* number of bits, modulo 2^64 (lsb first) */
    unsigned char buffer[64];   /* input buffer */
} MD5_CTX;

void MD5Init(MD5_CTX *context);
void MD5Update(MD5_CTX *context, const unsigned char *input, unsigned int inputLen);
void MD5Final(unsigned char digest[16], MD5_CTX *context);
void MD5str(const unsigned char *str, unsigned char digest[16]);

#endif

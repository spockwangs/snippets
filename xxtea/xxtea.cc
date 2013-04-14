#include "xxtea.h"

#include <cstdio>
#include <cassert>
#include <cerrno>
#include <error.h>
#include <cstdlib>
#include <cstring>
#include <arpa/inet.h>

using namespace std;

#define DELTA 0x9e3779b9
#define MX (((z>>5^y<<2) + (y>>3^z<<4)) ^ ((sum^y) + (k[(p&3)^e] ^ z)))
 
namespace {
    void btea(uint32_t *v, int n, uint32_t const k[4])
    {
         uint32_t y, z, sum;
         unsigned p, rounds, e;
         if (n > 1) {          /* Coding Part */
              rounds = 6 + 52/n;
              sum = 0;
              z = v[n-1];
              do {
                   sum += DELTA;
                   e = (sum >> 2) & 3;
                   for (p=0; p< (unsigned int) (n-1); p++) {
                        y = v[p+1]; 
                        z = v[p] += MX;
                   }
                   y = v[0];
                   z = v[n-1] += MX;
              } while (--rounds);
         } else if (n < -1) {  /* Decoding Part */
              n = -n;
              rounds = 6 + 52/n;
              sum = rounds*DELTA;
              y = v[0];
              do {
                   e = (sum >> 2) & 3;
                   for (p=n-1; p>0; p--) {
                        z = v[p-1];
                        y = v[p] -= MX;
                   }
                   z = v[n-1];
                   y = v[0] -= MX;
              } while ((sum -= DELTA) != 0);
         }
    }
}

void XXTEA::encrypt(const char in[], int len, const uint32_t key[4], char out[])
{
     assert(in != NULL && len > 0);
     assert(key != NULL);
     assert(out != NULL);

     // Pack in[] to uint32_t[].
     uint32_t *v = new uint32_t[len];
     for (int i = 0; i < len; i++) {
          v[i] = in[i];
     }

     btea(v, len, key);
     
     // Copy result to 'out[]'.
     for (int i = 0; i < len; i++) {
          uint32_t w = htonl(v[i]);
          out[4*i] = w & 0xFF;
          out[4*i+1] = (w >> 8) & 0xFF;
          out[4*i+2] = (w >> 16) & 0xFF;
          out[4*i+3] = (w >> 24) & 0xFF;
     }
     delete[] v;
}
          
void XXTEA::decrypt(const char in[], int len, const uint32_t key[4], char out[])
{
     assert(in != NULL && len > 0 && len%4 == 0);
     assert(key != NULL);
     assert(out != NULL);

     // Convert 'in[]' to uint32_t[].
     // Every 4 bytes are mapped to one element of 'v[]'.
     uint32_t *v = new uint32_t[len/4];
     for (int i = 0; i < len/4; i++) {
          v[i] = ((unsigned char) in[4*i] << 24)
               | ((unsigned char) in[4*i+1] << 16)
               | ((unsigned char) in[4*i+2] << 8)
               | (unsigned char) in[4*i+3];
     }
     
     btea(v, -len/4, key);
     
     // Convert result to bytes.
     for (int i = 0; i < len/4; i++) {
          out[i] = v[i] & 0xFF;
     }

     delete[] v;
}

void XXTEA::encrypt(const string& plain_text, const uint32_t key[4], string *p_secret_text)
{
     assert(!plain_text.empty());
     assert(key != NULL);
     assert(p_secret_text != NULL);

     // Pack in[] to uint32_t[].
     int len = plain_text.length();
     uint32_t *v = new uint32_t[len];
     for (int i = 0; i < len; i++) {
          v[i] = plain_text[i];
     }

     btea(v, len, key);
     
     // Copy result to 'out[]'.
     p_secret_text->clear();
     for (int i = 0; i < len; i++) {
          uint32_t w = htonl(v[i]);
          p_secret_text->push_back(w & 0xFF);
          p_secret_text->push_back((w >> 8) & 0xFF);
          p_secret_text->push_back((w >> 16) & 0xFF);
          p_secret_text->push_back((w >> 24) & 0xFF);
     }
     delete[] v;
}


void XXTEA::decrypt(const string& secret_text, const uint32_t key[4], string *p_plain_text)
{
     assert(!secret_text.empty() && secret_text.length()%4 == 0);
     assert(key != NULL);
     assert(p_plain_text != NULL);

     // Convert 'in[]' to uint32_t[].
     // Every 4 bytes are mapped to one element of 'v[]'.
     int len = secret_text.length();
     uint32_t *v = new uint32_t[len/4];
     for (int i = 0; i < len/4; i++) {
          v[i] = ((unsigned char) secret_text[4*i] << 24)
               | ((unsigned char) secret_text[4*i+1] << 16)
               | ((unsigned char) secret_text[4*i+2] << 8)
               | (unsigned char) secret_text[4*i+3];
     }
     
     // Decode.
     btea(v, -len/4, key);
     
     // Convert result to bytes.
     p_plain_text->clear();
     for (int i = 0; i < len/4; i++)
         p_plain_text->push_back(v[i] & 0xFF);

     delete[] v;
}

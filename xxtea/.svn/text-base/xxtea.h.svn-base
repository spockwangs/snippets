/* 
 * Implement the XXTEA encyrption algorithm.
 *
 * See Wikipedia for details.
 */

#ifndef __XXTEA_H
#define __XXTEA_H

#include <stdint.h>
#include <string>

namespace XXTEA {
    /* 
     * Encrypt the plain text 'in[]' which is 'len' bytes using the
     * key 'key[]' into 'out[]'.  'out[]' must have 4 times length of
     * 'in[]'.
     */
    void encrypt(const char in[], int len, const uint32_t key[4], char out[]);

    /* 
     * Decrypt the encrypted text 'in[]' which is 'len' bytes using
     * the key 'key[]' into 'out[]'.  'out[]' must have a fourth of
     * length of 'in[]'.
     */
    void decrypt(const char in[], int len, const uint32_t key[4], char out[]);

    void encrypt(const std::string& plain_text, const uint32_t key[4], std::string *p_secret_text);

    void decrypt(const std::string& secret_text, const uint32_t key[4], std::string *p_plain_text);
}

#endif

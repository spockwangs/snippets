#include "xxtea.h"
#include <cstdio>
#include <cstdlib>
#include <string>

using namespace std;

string toHexString(const string& str)
{
    char buf[2];
    string result;
    for (int i = 0; (size_t) i < str.length(); i++) {
        sprintf(buf, "%02x", str[i]);
        result.push_back(buf[0]);
        result.push_back(buf[1]);
    }
    return result;
}

int main(int argc, char *argv[])
{
     const uint32_t key[] = {
          0x1, 0x2, 0x3, 0x4
     };

     if (argc < 2) {
         printf("Usage: %s string\n", argv[0]);
          exit(1);
     }
     
     // Encoding.
     string plain_text(argv[1]);
     string secret_text;
     XXTEA::encrypt(plain_text, key, &secret_text);
     printf("%s -> %s\n", plain_text.c_str(), toHexString(secret_text).c_str());

     // Decoding.
     XXTEA::decrypt(secret_text, key, &plain_text);
     printf("%s -> %s\n", toHexString(secret_text).c_str(), plain_text.c_str());
     return 0;
}

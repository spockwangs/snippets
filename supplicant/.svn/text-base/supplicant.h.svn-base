#ifndef __SUPPLICANT_H
#define __SUPPLICANT_H

#define LIBNET_LIL_ENDIAN  1
#include <libnet.h>
#include <pcap.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <error.h>
#include <netinet/ether.h>
#include <sys/select.h>
#include <errno.h>
#include <assert.h>

extern const char *dev;

enum {                          // type of EAP packet
    EAP_PACKET = 0x00,
    EAPOL_START = 0x01,
    EAPOL_LOGOFF = 0x02,
    EAPOL_KEY = 0x03,

    // index of fields in Ethernet frame
    ETHER_TYPE      = 12,   // 2 bytes
    ETHER_VERSION   = 14,   // 1 byte

    EAPOL_TYPE  = 15,   // 1 byte
    EAPOL_LEN   = 16,   // 2 bytes

    EAP_CODE    = 18,   // 1 byte
    EAP_ID      = 19,   // 1 byte
    EAP_LEN     = 20,   // 2 bytes
    EAP_TYPE    = 22,   // 1 byte

    // EAP type; code field of EAP frame
    EAP_REQUEST    = 1,
    EAP_RESPONSE   = 2,
    EAP_SUCCESS    = 3,
    EAP_FAILURE    = 4,
    
    // EAP Request/Response type
    EAP_IDENTITY        = 1,
    EAP_NOTIFICATION    = 2,
    EAP_NAK             = 3,
    EAP_MD5_CHALLENGE   = 4,
    EAP_OTP             = 5,
    EAP_GTC             = 6,
    EAP_EXPAND          = 254,
    EAP_EXPERIMENT      = 255,
};


extern uint32_t my_key;
extern uint32_t serialNO;

#endif  /* ! __SUPPLICANT_H */

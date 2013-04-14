#ifndef __SEND_H
# define __SEND_H

# include "supplicant.h"

void send_eap_start(struct libnet_link_int *l, struct ether_addr *dst,
                    struct ether_addr *src);
void send_eap_identity(struct libnet_link_int *l, struct ether_addr *dst,
                       struct ether_addr *src, u_char id, char *username);
void send_eap_md5(struct libnet_link_int *l, struct ether_addr *dst,
                  struct ether_addr *src, u_char id, const char *username,
                  const char *password, u_char * packet, u_char length);
void send_eap_echo(struct libnet_link_int *l, struct ether_addr *dst,
                   struct ether_addr *src, uint32_t key);
unsigned char Alog(unsigned char BForAlog);
u_char encode(u_char byte);

#endif

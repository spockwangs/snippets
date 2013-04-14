/*
 * Supplicant program based on IEEE 802.1X-2004.
 *
 * Bug
 *   Due to some private echo packets used by Ruijie authenticator, it can
 *   only keep the connection for around 20 seconds before being
 *   disconnected.  And then it will reestablish connections and hold it
 *   for another 20 seconds or so, and it tries to establish connections
 *   again and so on.
 */


#include "md5.h"
#include "send.h"
#include "supplicant.h"

        /* global variables */
const int debug = 1;

const char *dev = "eth0";   // which interface needs authentication
static char username[] = "hgg11004";
static char password[] = "204531";

typedef enum State State;
enum State {
    LOG_START,
    USERNAME,
    PASSWORD,
    SUCCESS,
    FAILURE,
};
static State state;

uint32_t my_key;
uint32_t serialNO;


        /* function declarations */
static int waiting_for(pcap_t *pcap_hdl, u_char const **pkt, int sec, struct pcap_pkthdr *phdr);


int main(void)
{
    // Multicast MAC Addr for finding authentication server; 
    // See IEEE 802.1X-2004, p31.
    struct ether_addr m_hwaddr = {      
        { 0x01, 0x80, 0xC2, 0x00, 0x00, 0x03 } 
    }; 
    char errbuf[PCAP_ERRBUF_SIZE];      // error buffer for libnet and libpcap
    struct libnet_link_int *l;          // handle to libnet
    struct ether_addr *my_hwaddr;       // local MAC addr
    pcap_t *pcap_hdl;                   // handle to libpcap
    struct bpf_program fp;              // hold compiled program
    bpf_u_int32 maskp;                  // mask of local network
    bpf_u_int32 netp;                   // net of local network
    const u_char *packet;
    struct pcap_pkthdr hdr;
    struct ether_addr auth_hwaddr;      // MAC addr of authenticating server

    /*
     * Initialization ...
     */

    // Open libnet device.
    l = libnet_open_link_interface((char *) dev, errbuf);
    if (l == NULL) {
        error(1, 0, "libnet_open_link_interface: %s", errbuf);
    }

    // Get local MAC address.
    my_hwaddr = libnet_get_hwaddr(l, dev, errbuf);
    if (my_hwaddr == NULL) {
        error(EXIT_FAILURE, 0, "libnet_get_hwaddr: %s", errbuf);
    }

    // Open libpcap device.
    pcap_hdl = pcap_open_live(dev, 128, 0, -1, errbuf);
    if (pcap_hdl == NULL) {
        error(EXIT_FAILURE, 0, "pcap_open_live: %s", errbuf);
    }

    // Set pcap filter to capture EAP packet which destined to me.
    char filter_exp[100];       // I guess it is big enough.
    pcap_lookupnet(dev, &netp, &maskp, errbuf);
    snprintf(filter_exp, sizeof(filter_exp), 
            "ether[12]=0x88 and ether[13]=0x8E and ether dst %x:%x:%x:%x:%x:%x", 
            my_hwaddr->ether_addr_octet[0], my_hwaddr->ether_addr_octet[1],
            my_hwaddr->ether_addr_octet[2], my_hwaddr->ether_addr_octet[3],
            my_hwaddr->ether_addr_octet[4], my_hwaddr->ether_addr_octet[5]);
    if (pcap_compile(pcap_hdl, &fp, filter_exp, 0, netp) == -1) {
        error(EXIT_FAILURE, 0, "pcap_compile() error");
    }
    if (pcap_setfilter(pcap_hdl, &fp) == -1) {
        error(EXIT_FAILURE, 0, "pcap_setfilter() error");
    }
    pcap_freecode(&fp);

    /*
     * Do the real stuff.
     * As a whole it is a Finite State Machine.
     */

    state = LOG_START;
    u_char id;
    int r, errors = 0;
    while (1) {
        switch (state) {
        case LOG_START:     // Send EAPOL Logstart message.
            send_eap_start(l, &m_hwaddr, my_hwaddr);

            r = waiting_for(pcap_hdl, &packet, 1, &hdr);
            if (r < 0) {            // error
                goto done;
            } else if (r == 0) {    // timeout
                continue;
            } else {                // a frame came
                if (packet != NULL && packet[EAP_CODE] == EAP_REQUEST && 
                    packet[EAP_TYPE] == EAP_IDENTITY) {
                    memmove(&auth_hwaddr, packet+6, 6);
                    state = USERNAME;
                    errors = 0;
                } else {
                    errors++;
                    sleep(1);   // retry after 1 sec
                }
            }
            if (errors >= 3) {
                fprintf(stderr, "Authentication server may not exists, exiting.\n");
                goto done;
            }
            break;
        case USERNAME:  // Sending username.
            id = packet[EAP_ID];
            send_eap_identity(l, &auth_hwaddr, my_hwaddr, id, username);
            if (debug)
                printf("Sending username ... \n");

            r = waiting_for(pcap_hdl, &packet, 1, &hdr);
            if (r < 0) {
                goto done;
            } else if (r == 0) {    // timeout
                continue;
            } else { 
                if (packet[EAP_CODE] == EAP_REQUEST &&
                    packet[EAP_TYPE] == EAP_MD5_CHALLENGE) {
                    state = PASSWORD;
                    errors = 0;
                } else {
                    if (debug) {
                        printf("Expecting MD5-Challenge, but got code = %d, type = %d\n",
                                packet[EAP_CODE], packet[EAP_TYPE]);
                    }
                    errors++;
                }
                if (errors >= 3) {
                    fprintf(stderr, "Authentication server may not exists, exiting.\n");
                    goto done;
                }
            }
            break;
        case PASSWORD:
            id = packet[EAP_ID];
            send_eap_md5(l, &auth_hwaddr, my_hwaddr, id, username, password, 
                    (u_char *) (packet+EAP_TYPE+2), packet[EAP_TYPE+1]);
            if (debug) 
                printf("Sending password ... \n");

            r = waiting_for(pcap_hdl, &packet, 1, &hdr);
            if (r == -1) {
                goto done;
            } else if (r == 0) {    // timeout
                continue;
            } 
            if (packet[EAP_CODE] == EAP_SUCCESS) {
                state = SUCCESS;

                serialNO = 0x102B;
                int offset;
                offset = 0x1C+packet[0x1b]+0x69+24;
                u_char *base = (u_char *) (&my_key);
                my_key = ntohl(* (uint32_t *)(packet+offset));
                int i;
                for (i = 0; i < 4; i++) {
                    base[i] = encode(base[i]);
                }

                errors = 0;
                if (debug)
                    printf("Authentication success!\n");
            } else if (packet[EAP_CODE] == EAP_FAILURE) {
                state = FAILURE;
                errors = 0;
                if (debug)
                    printf("Authentication failure!\n");
            } else {
                if (debug)
                    printf("Expecting Success or Failure, but got code = %d\n",
                            packet[EAP_CODE]);
                errors++;
                if (errors >= 3) {
                    fprintf(stderr, "Authentication server may not exist, exiting ...\n");
                    goto done;
                }
            }
            break;
        case SUCCESS:
            send_eap_echo(l, &auth_hwaddr, my_hwaddr, my_key);

            r = waiting_for(pcap_hdl, &packet, 4, &hdr);
            if (r == -1) {
                goto done;
            } else if (r == 0) {    // timeout
                continue;
            } else { 
                if (packet != NULL && packet[EAP_CODE] == EAP_FAILURE) {
                    if (debug)
                        printf("Authentication failure!\n");
                    state = FAILURE;
                }
            }
            break;
        case FAILURE:
            sleep(1);
            state = LOG_START;
            if (debug)
                printf("Retry authenticating ... \n");
            errors = 0;
            break;
        default:    // should never reach here
            assert(0);
        }
    }

done:
    libnet_close_link_interface(l);
    pcap_close(pcap_hdl);

    return 0;
}


/*
 * waiting_for --
 *   Waiting for a packet or 'sec' seconds.  Return -1 if IO error, 0
 *   if timeout or 1 if a packet comes.  If a packet comes the pointer
 *   to the packet is stored in 'pkt'.
 */
static int waiting_for(pcap_t *pcap_hdl, u_char const **pkt, int sec, struct pcap_pkthdr *phdr)
{
    fd_set readfds;
    struct timeval timeout;
    int r, fd;

    fd = pcap_fileno(pcap_hdl);
    FD_ZERO(&readfds);
    FD_SET(fd, &readfds);
    timeout.tv_sec = sec;
    timeout.tv_usec = 0;

    r = select(fd+1, &readfds, NULL, NULL, &timeout);
    if (r == -1) {
        error(0, errno, "select error");
        return -1;
    } else if (r == 0) {    // timeout
        return 0;
    } else { 
        *pkt = pcap_next(pcap_hdl, phdr);
        return 1;
    }
}

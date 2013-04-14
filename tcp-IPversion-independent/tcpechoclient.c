/*
 * tcpechoclient - A simple tcp echo client.
 *
 * It is an example of IP version independent client program.
 */

#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/unistd.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <error.h>
#include <assert.h>
#include <signal.h>

int writen(int fd, char *buf, int len);
void str_cli(FILE *in, int sockfd);
int max(int a, int b);

#define MAXLINE 1024

int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("Usage: %s server port\n", argv[0]);
        exit(1);
    }
    
    struct addrinfo hints, *res, *aip;
    int sockfd, r;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family   = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    r = getaddrinfo(argv[1], argv[2], &hints, &res);
    if (r != 0) {
        error(1, 0, "getaddrinfo error: %s", gai_strerror(r));
    }

    for (aip = res; aip; aip = aip->ai_next) {
        sockfd = socket(aip->ai_family, aip->ai_socktype, aip->ai_protocol);
        if (sockfd < 0)
            continue;

        if (connect(sockfd, aip->ai_addr, aip->ai_addrlen) == 0)
            break;

        close(sockfd);
    }
    if (aip == NULL)
        error(1, 0, "connect error for %s:%s", argv[1], argv[2]);
    freeaddrinfo(res);

    signal(SIGPIPE, SIG_IGN);

    str_cli(stdin, sockfd);

    return 0;
}


void str_cli(FILE *in, int sockfd)
{
    int stdineof;
    fd_set rset;
    char buf[MAXLINE];
    int n;

    stdineof = 0;
    FD_ZERO(&rset);
    for (;;) {
        if (stdineof == 0)
            FD_SET(fileno(in), &rset);
        FD_SET(sockfd, &rset);
        int maxfdp1 = max(fileno(in), sockfd) + 1;

        n = select(maxfdp1, &rset, NULL, NULL, NULL);
        if (n < 0) {
            if (errno == EINTR)
                continue;
            else
                error(1, errno, "select error");
        }

        if (FD_ISSET(sockfd, &rset)) {
            if ((n = read(sockfd, buf, MAXLINE)) == 0) {
                if (stdineof)
                    return;
                else
                    error(1, 0, "str_cli: server terminated prematurely");
            }
            write(fileno(stdout), buf, (size_t) n);
        }

        if (FD_ISSET(fileno(in), &rset)) {
            if ((n = read(fileno(in), buf, MAXLINE)) == 0) {
                stdineof = 1;
                shutdown(sockfd, SHUT_WR);
                FD_CLR(fileno(in), &rset);
                continue;
            }
            if (writen(sockfd, buf, n) < 0)
                error(1, errno, "write error");
        }
    }
}


int writen(int fd, char *buf, int len)
{
    assert(buf != NULL && len > 0);

    int nleft, idx;

    nleft = len;
    idx = 0;
    while (nleft > 0) {
        int n = write(fd, &buf[idx], (size_t) nleft);
        if (n < 0) {
            if (errno == EINTR)
                continue;
            else
                return -1;
        }
        nleft -= n;
        idx += n;
    }
    assert(nleft == 0);
    return len;
}


int max(int a, int b)
{
    return (a > b ? a : b);
}

/*
 * tcpechoserver - A simple TCP echo server
 *
 * It is an example of IP version independent server program.
 *
 * Bug
 *   Must be root to run this because it has to listen to port number less
 *   than 1024.
 */

#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/unistd.h>
#include <sys/select.h>
#include <sys/wait.h>
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

// Function declarations
int writen(int fd, char *buf, int len);
void do_echo(int fd);
void on_child(int signum);

#define MAXSOCK 2  // listen 2 sockets: one for IPv6, one for IPv4
#define MAXLINE 1024

// Global variables
const char *SERVICE = "echo";

int main()
{
    struct addrinfo hints, *res, *aip;
    int r, sockfd[MAXSOCK], nsock=0;

    memset(&hints, 0, sizeof(hints));
    hints.ai_flags = AI_PASSIVE;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    r = getaddrinfo(NULL, SERVICE, &hints, &res);
    if (r != 0) {
        error(1, 0, "getaddrinfo error: %s", gai_strerror(r));
    }

    for (aip = res; aip && nsock < MAXSOCK; aip = aip->ai_next) {
        sockfd[nsock] = socket(aip->ai_family, aip->ai_socktype, aip->ai_protocol);
        if (sockfd[nsock] < 0)
            continue;

        if (aip->ai_family == AF_INET6) {
            int on = 1;
            setsockopt(sockfd[nsock], IPPROTO_IPV6, IPV6_V6ONLY,
                       (char *)&on, sizeof(on));
            /* errors are ignored */
        }
        if (bind(sockfd[nsock], aip->ai_addr, aip->ai_addrlen) < 0 ) {
            close(sockfd[nsock]);
            continue;
        }
        if (listen(sockfd[nsock], SOMAXCONN) < 0) {
            close(sockfd[nsock]);
            continue;
        }
        nsock++;
    }
    if (nsock == 0)
        error(1, 0, "listen error for service %s", SERVICE);
    freeaddrinfo(res);

    /*
     * Listen on one or both of sockfd[].
     */

    signal(SIGCHLD, on_child);
    signal(SIGPIPE, SIG_IGN);
    int maxfd = -1;
    fd_set allset, rset;
    FD_ZERO(&allset);
    for (int i = 0; i < nsock; i++) {
        FD_SET(sockfd[i], &allset);
        if (sockfd[i] > maxfd)
            maxfd = sockfd[i];
    }
    for (;;) {
        rset = allset;
        int nready = select(maxfd+1, &rset, NULL, NULL, NULL);
        if (nready < 0) {
            if (errno == EINTR)
                continue;
            else
                error(1, errno, "select error");
        }
        for (int i = 0; i < nsock; i++) {
            if (FD_ISSET(sockfd[i], &rset)) {
                int connfd = accept(sockfd[i], NULL, NULL);
                if (connfd < 0) {
                    switch (errno) {
                    case EINTR:
                    case ECONNABORTED:
                        // ignore
                        break;
                    default:
                        error(1, errno, "accept error");
                    }
                } else {
                    if (fork() == 0) {
                        for (int i = 0; i < nsock; i++)
                            close(sockfd[i]);
                        do_echo(connfd);
                        close(connfd);
                        exit(0);
                    }
                    close(connfd);
                }
                
                if (--nready <= 0)
                    break;
            }
        }
    }
}


void do_echo(int fd)
{
    int n;
    char buf[MAXLINE];
    
    while ((n = read(fd, buf, MAXLINE)) > 0) {
        writen(fd, buf, n);
    }
}


int writen(int fd, char *buf, int len)
{
    assert(buf != NULL && len >= 0);
    
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


void on_child(int signum)
{
    (void) signum;
    while (waitpid(-1, NULL, WNOHANG) > 0)
        ;
    return;
}

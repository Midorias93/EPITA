#define _POSIX_C_SOURCE 200809L

#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "server.h"

int creat_and_bind(struct server_config server)
{
    struct addrinfo hints = { 0 };
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    struct addrinfo *res = NULL;

    if (getaddrinfo(server.ip, server.port, &hints, &res) == -1)
    {
        fprintf(stderr, "getaddrinfo failed");
        return -1;
    }
    int sock = -1;
    for (struct addrinfo *p = res; p; p = p->ai_next)
    {
        sock = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if(sock == -1)
            continue;

        if (bind(sock, p->ai_addr, p->ai_addrlen) != -1)
            break;

        close(sock);
        sock = -1;
    }

    freeaddrinfo(res);
    return sock;
}

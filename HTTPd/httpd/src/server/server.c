#define _POSIX_C_SOURCE 200809L

#include "server.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

void start_server(int socket_server)
{
    int client_socket;
    char buffer[256];
    if (listen(socket_server, 5) == -1)
    {
        fprintf(stderr, "listen failed\n");
        return;
    }
    while (1)
    {
        if ((client_socket = accept(socket_server, NULL, NULL)) == -1)
        {
            fprintf(stderr, "accept failed\n");
            return;
        }
        if (client_socket != -1)
        {
            printf("un utilisateur c connecte\n");
            send(client_socket, "connexion au server de romain\n",
                    strlen("connexion au server de romain\n"), 0);

            int size_message = 0;
            while ((size_message = recv(client_socket, buffer, 256, 0)) > 0)
            {
                printf("donnees recues du client : %.*s", size_message, buffer);
                send(client_socket, buffer, size_message, 0);
            }
        }
    }
}

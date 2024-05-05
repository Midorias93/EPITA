#define _POSIX_C_SOURCE 200809L

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "daemon.h"
#include "../server/server.h"


/*void handler(int signum)
{
    switch (signum)
    {
    case SIGINT:
        printf("fermeture du serveur\n");
        exit(1);
        break;
    }
}

static int setup_signal(void)
{
    struct sigaction sa;
    sa.sa_flags = 0;
    sa.sa_handler = handler;
    if (sigemptyset(&sa.sa_mask) < 0)
    {
        return 1;
    }
    if (sigaction(SIGINT, &sa, NULL) < 0)
    {
        return 1;
    }
    if (sigaction(SIGUSR1, &sa, NULL) < 0)
    {
        return 1;
   }
    return 0;
}*/

void start_deamon(int socket_server, struct config *config)
{
    int pid = fork();
    if (pid != 0)
    {
        close(socket_server);
        sauv_pid(config->pid_file, pid);
        exit(1);
    }
    else
    {
        // setup_signal();
        start_server(socket_server);
    }
}

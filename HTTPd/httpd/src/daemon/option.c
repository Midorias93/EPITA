#define _POSIX_C_SOURCE 200809L

#include <signal.h>
#include <stdio.h>

#include "daemon.h"
#include "../server/server.h"

void start(int is_a_life, struct config *config, int socket_server)
{
    if (!is_a_life)
    {
        start_deamon(socket_server, config);
    }
}

void stop(int pid, int is_a_life, struct config *config)
{
    if (is_a_life)
    {
        kill(pid, SIGINT);
        remove(config->pid_file);
    }
}

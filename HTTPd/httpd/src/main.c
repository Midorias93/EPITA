#define _POSIX_C_SOURCE 200809L

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "server/server.h"
#include "daemon/daemon.h"

int main(int nb_arg, char *argl[])
{
    struct arg *arg = parse_arg(nb_arg, argl, init_arg());
    if (arg == NULL || check_arg(arg))
    {
        fprintf(stderr, "les arguments ne sont pas correct\n");
        exit(1);
    }

    struct config *config = parse_configuration(arg->config_file);
    int server_socket = -1;
    if (arg->option == 0)
    {
        server_socket = creat_and_bind(config->servers[0]);
        if(server_socket == -1)
        {
            fprintf(stderr, "socket failed");
        }
        start_server(server_socket);
    }
    else
    {
        int pid = get_pid(config->pid_file);
        int is_a_life = is_deamon_a_life(pid);
        if (!is_a_life)
        {
            server_socket = creat_and_bind(config->servers[0]);
            if(server_socket == -1)
            {
                fprintf(stderr, "socket failed");
            }
        }
        switch(arg->option)
        {
            case START:
                start(is_a_life, config, server_socket);
                break;
            case STOP:
                stop(pid, is_a_life, config);
                break;
            case RESTART:
                stop(pid, is_a_life, config);
                start(!is_a_life, config, server_socket);
                break;
        }

        if (server_socket != -1)
        {
            close(server_socket);
        }

        return 0;
    }
}

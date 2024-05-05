#ifndef SERVER_H
#define SERVER_H

#include "../config/config.h"

enum
{
    START = 1,
    STOP,
    RESTART,
    RELOAD,
};

struct arg
{
    char *config_file;
    int option;
    int dry_run;
};

struct arg *init_arg(void);
struct arg *parse_arg(int nb_arg, char *argl[], struct arg *arg);
int check_arg(struct arg *arg);

int creat_and_bind(struct server_config server);

void start_server(int socket_server);

#endif // SERVER_H

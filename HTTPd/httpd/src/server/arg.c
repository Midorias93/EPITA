#include <stdlib.h>
#include <string.h>

#include "server.h"

struct arg *init_arg(void)
{
    struct arg *arg = malloc(sizeof(struct arg));
    arg->config_file = NULL;
    arg->option = 0;
    arg->dry_run = 0;
    return arg;
}

static int equivalence_option(char *option)
{
    if (strcmp(option, "start") == 0)
    {
        return START;
    }
    else if (strcmp(option, "stop") == 0)
    {
        return STOP;
    }
    else if (strcmp(option, "restart") == 0)
    {
        return RESTART;
    }
    else if (strcmp(option, "reload") == 0)
    {
        return RELOAD;
    }
    else
    {
        return 0;
    }
}

struct arg *parse_arg(int nb_arg, char *argl[], struct arg *arg)
{
    if (nb_arg < 2)
    {
        free(arg);
        return NULL;
    }
    else
    {
        for (int i = 1; i < nb_arg; i++)
        {
            if (strcmp(argl[i], "--dry-run") == 0)
            {
                arg->dry_run = 1;
            }
            else if (strcmp(argl[i], "-a") == 0)
            {
                if (i + 1 >= nb_arg)
                {
                    free(arg);
                    return NULL;
                }
                else
                {
                    arg->option = equivalence_option(argl[++i]);
                }
            }
            else if (i == nb_arg - 1)
            {
                arg->config_file = argl[i];
            }
            else
            {
                free(arg);
                return NULL;
            }
        }
    }
    return arg;
}

int check_arg(struct arg *arg)
{
    if (arg->config_file == NULL || arg->option == -1)
    {
        return 1;
    }
    return 0;
}

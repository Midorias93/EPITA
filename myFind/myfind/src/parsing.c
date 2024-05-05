#include <string.h>

#include "fifo/fifo.h"
#include "my_find.h"
#include "option.h"
#include "token/token.h"

static int condition1(char *str)
{
    if (strcmp(str, "-o") != 0 && strcmp(str, "-a") != 0
        && strcmp(str, "(") != 0 && strcmp(str, "!") != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

static int condition2(char *str)
{
    if (strcmp(str, "-o") != 0 && strcmp(str, "-a") != 0
        && strcmp(str, ")") != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int is_action(int type)
{
    if (type == PRINT)
    {
        return PRINT;
    }
    else if (type == DELETE)
    {
        return DELETE;
    }
    else if (type == EXEC)
    {
        return EXEC;
    }
    else if (type == EXECP)
    {
        return EXECP;
    }
    else if (type == EXECDIR)
    {
        return EXECDIR;
    }
    else
    {
        return -1;
    }
}

static struct fifo *gestion_error(struct info *info, struct fifo *file)
{
    info->erreur = 1;
    fifo_destroy(file);
    return NULL;
}

struct fifo *fait_la_file(struct info *info, int argc, char *argv[])
{
    struct fifo *file = fifo_init();
    struct token *token = NULL;
    int type = -1;
    for (int i = info->depart; i < argc;)
    {
        type = donne_type(argv[i]);
        if (type == -1)
        {
            info->erreur = 1;
            fifo_destroy(file);
            return NULL;
        }
        info->action = is_action(type);
        info->option = info->action == DELETE ? D : info->option;
        if (possed_un_argument(type))
        {
            if (i == argc - 1)
            {
                return gestion_error(info, file);
            }
            token = init_token(argv[++i], type);
        }
        else
        {
            token = init_token(NULL, type);
        }
        fifo_push(file, token);
        if (i + 1 != argc && condition1(argv[i]))
        {
            if (!condition2(argv[i + 1]))
            {
                i++;
                continue;
            }
            else
            {
                token = init_token(NULL, AND);
                fifo_push(file, token);
            }
        }
        i++;
    }
    if (file->size == 0)
    {
        fifo_destroy(file);
        return NULL;
    }
    return file;
}

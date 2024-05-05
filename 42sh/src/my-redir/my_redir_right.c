#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>

#include "my_redir.h"

int my_redir_single_right_chevron_open(struct redir_tree *redir_tree)
{
    redir_tree->fd = open(redir_tree->filename, O_RDWR);
    if (fcntl(redir_tree->fd, F_GETFL) == -1)
    {
        return 1;
    }
    // si il a pas un ionumber
    if (redir_tree->ionumber == -1)
    {
        redir_tree->save = dup(0);
        dup2(redir_tree->fd, 0);
    }
    // si il un ionumber
    else
    {
        redir_tree->save = dup(redir_tree->ionumber);
        dup2(redir_tree->fd, redir_tree->ionumber);
    }
    return 0;
}

// je sais pas si faut close a la fin (pour l'instant ca le clause)
int my_redir_single_right_chevron_and_open(struct redir_tree *redir_tree)
{
    redir_tree->fd = atoi(redir_tree->filename);
    if (fcntl(redir_tree->fd, F_GETFL) == -1)
    {
        return 1;
    }
    // si il a pas un ionumber
    if (redir_tree->ionumber == -1)
    {
        redir_tree->save = dup(0);
        dup2(redir_tree->fd, 0);
    }
    // si il un ionumber
    else
    {
        redir_tree->save = dup(redir_tree->ionumber);
        dup2(redir_tree->fd, redir_tree->ionumber);
    }
    return 0;
}

// je pense il manque des trucs
int my_redir_right_and_left_chevron_open(struct redir_tree *redir_tree)
{
    redir_tree->fd = open(redir_tree->filename, O_WRONLY | O_CREAT | O_TRUNC);
    chmod(redir_tree->filename, 0644);
    dup2(redir_tree->fd, redir_tree->save);
    return 1;
}

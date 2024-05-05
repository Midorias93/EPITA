#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>

#include "my_redir.h"

int my_redir_single_left_chevron_open(struct redir_tree *redir_tree)
{
    redir_tree->fd = open(redir_tree->filename, O_WRONLY | O_CREAT | O_TRUNC);
    chmod(redir_tree->filename, 0644);
    // si il a pas un ionumber
    if (redir_tree->ionumber == -1)
    {
        redir_tree->save = dup(1);
        dup2(redir_tree->fd, 1);
    }
    // si il un ionumber
    else
    {
        redir_tree->save = dup(redir_tree->ionumber);
        dup2(redir_tree->fd, redir_tree->ionumber);
    }
    return 0;
}

void my_redir_close(struct redir_tree *redir_tree)
{
    if (redir_tree->next)
        my_redir_close(redir_tree->next);
    close(redir_tree->fd);
    // il a un io
    if (redir_tree->ionumber != -1)
    {
        dup2(redir_tree->save, redir_tree->ionumber);
    }
    // il a pas de io
    else
    {
        dup2(redir_tree->save, 1);
    }
    close(redir_tree->save);
}

// je sais pas il fait quoi ce truc de con
int my_redir_single_left_chevron_pipe_open(struct redir_tree *redir_tree)
{
    return my_redir_double_left_chevron_open(redir_tree);
}

int my_redir_double_left_chevron_open(struct redir_tree *redir_tree)
{
    redir_tree->fd = open(redir_tree->filename, O_RDWR | O_CREAT | O_APPEND);
    chmod(redir_tree->filename, 0644);
    // si il a pas un ionumber
    if (redir_tree->ionumber == -1)
    {
        redir_tree->save = dup(1);
        dup2(redir_tree->fd, 1);
    }
    // si il un ionumber
    else
    {
        redir_tree->save = dup(redir_tree->ionumber);
        dup2(redir_tree->fd, redir_tree->ionumber);
    }
    return 0;
}

int my_redir_single_left_chevron_and_open(struct redir_tree *redir_tree)
{
    redir_tree->fd = atoi(redir_tree->filename);
    if (fcntl(redir_tree->fd, F_GETFL) == -1)
    {
        return 1;
    }
    // si il a pas un ionumber
    if (redir_tree->ionumber == -1)
    {
        redir_tree->save = dup(1);
        dup2(redir_tree->fd, 1);
    }
    // si il un ionumber
    else
    {
        redir_tree->save = dup(redir_tree->ionumber);
        dup2(redir_tree->fd, redir_tree->ionumber);
    }
    return 0;
}

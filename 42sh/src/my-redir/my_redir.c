#include "my_redir.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#include "../exec/exec.h"

static struct redir_tree *new_tree(struct ast_redir *ast)
{
    struct redir_tree *tree = malloc(sizeof(struct redir_tree));
    tree->filename = ast->word;
    tree->save = -1;
    if (ast->io_number < 0)
        tree->ionumber = -1;
    else
        tree->ionumber = ast->io_number;
    tree->fd = -1;
    tree->token = ast->redir;
    tree->next = NULL;
    tree->prev = NULL;

    return tree;
}

struct redir_tree *add_tree(struct ast_redir *ast, struct redir_tree *tree)
{
    struct redir_tree *new_t = new_tree(ast);
    if (!tree)
        return new_t;

    struct redir_tree *tmp = tree;
    while (tmp->next != NULL)
        tmp = tmp->next;

    tmp->next = new_t;
    new_t->prev = tmp;

    return tree;
}

void free_redir_tree(struct redir_tree *tree)
{
    while (tree != NULL)
    {
        struct redir_tree *tmp = tree->next;
        free(tree);
        tree = tmp;
    }
}

#ifndef MY_REDIR_H
#define MY_REDIR_H

#include "../ast/ast.h"

struct redir_tree
{
    char *filename; // Can be ionumber to
    int save;
    int fd;
    int ionumber;
    char *token;
    struct redir_tree *next;
    struct redir_tree *prev;
};

int my_redir_single_left_chevron_open(struct redir_tree *redir_tree);
int my_redir_single_left_chevron_pipe_open(struct redir_tree *redir_tree);
int my_redir_single_right_chevron_open(struct redir_tree *redir_tree);
int my_redir_double_left_chevron_open(struct redir_tree *redir_tree);
int my_redir_single_right_chevron_and_open(struct redir_tree *redir_tree);
int my_redir_single_left_chevron_and_open(struct redir_tree *redir_tree);
int my_redir_right_and_left_chevron_open(struct redir_tree *redir_tree);
void my_redir_close(struct redir_tree *redir_tree);

struct redir_tree *add_tree(struct ast_redir *ast, struct redir_tree *tree);
void free_redir_tree(struct redir_tree *tree);

#endif // MY_REDIR_H

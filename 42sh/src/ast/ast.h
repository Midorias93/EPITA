#ifndef AST_H
#define AST_H

#include <unistd.h>

#include "../lexer/token.h"

enum ast_type
{
    AST_INPUT,
    AST_LIST,
    AST_ANDOR,
    AST_PIPELINE,
    AST_CMD,
    AST_SIMPLECMD,
    AST_SHELLCMD,
    AST_FUNCDEC,
    AST_REDIR,
    AST_PREFIX,
    AST_ELEMENT,
    AST_COMPOUND,
    AST_FOR,
    AST_WHILE,
    AST_UNTIL,
    AST_IF,
    AST_ELSE
};

struct ast_input
{
    struct ast_list *list;
};

struct ast_list
{
    size_t nb;
    struct ast_andor **andor;

    size_t nb_data;
    enum token_type *data;
};

struct ast_andor
{
    size_t nb;
    struct ast_pipeline **pipeline;

    enum token_type *data; // first operator is between first
                           // and second pipeline (size: nb - 1)
};

struct ast_pipeline
{
    size_t nb;
    struct ast_cmd **cmd;

    int is_neg;
};

enum cmd_type
{
    SIMPLE,
    SHELL,
    FUNCTION,
};

struct ast_cmd
{
    size_t nb;
    struct ast_redir **redir;

    enum cmd_type type;
    void *cmd;
};

struct ast_simplecmd
{
    size_t nb_prefix;
    struct ast_prefix **prefix;

    int is_word;
    char *word;

    size_t nb_element;
    struct ast_element **elements;
};

struct ast_shellcmd
{
    enum ast_type child_type;
    void *child;
    int is_subshell;
};

struct ast_funcdec
{
    int is_check;
    char *word;
    struct ast_shellcmd *child;
};

struct ast_redir
{
    int io_number; // If negative no ionumber
    char *redir;
    char *word;
};

struct ast_prefix
{
    int is_redir;
    void *child;
};

struct ast_element
{
    int is_redir;
    void *child;
};

struct ast_compound
{
    int nb;
    struct ast_andor **andor;

    size_t nb_data;
    enum token_type *data;
};

struct ast_for
{
    char *word;

    int nb;
    char **words;

    struct ast_compound *compound;
};

struct ast_while
{
    struct ast_compound *condition;
    struct ast_compound *compound;
};

struct ast_until
{
    struct ast_compound *condition;
    struct ast_compound *compound;
};

struct ast_if
{
    struct ast_compound *condition;
    struct ast_compound *compound;
    struct ast_else *else_clause; // Possibly NULL
};

struct ast_else
{
    int is_else;

    struct ast_compound *condition; // Possibly NULL
    struct ast_compound *compound;
    struct ast_else *else_clause; // Possibly NULL
};

/**
 *
 ** \brief Allocate a new ast with the given type
 */
void *ast_new(enum ast_type type);

/**
 ** \brief Recursively free the given ast
 */
void ast_free(struct ast_input *ast);
struct ast *search_next(struct ast_input *ast);
void free_redir(struct ast_redir *ast);
void free_prefix(struct ast_prefix *ast);
void free_element(struct ast_element *ast);
void free_cmd(struct ast_cmd *ast);
void free_andor(struct ast_andor *ast);
void free_shellcmd(struct ast_shellcmd *ast);
void ast_print(struct ast_input *ast);
void print_funcdec(struct ast_funcdec *ast, int *j);

#endif /* !AST_H */

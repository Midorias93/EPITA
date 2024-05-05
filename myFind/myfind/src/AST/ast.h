#ifndef AST_H
#define AST_H

#include "../fifo/fifo.h"
#include "../info.h"
#include "../stack/stack.h"

struct ast
{
    struct token *data;
    struct ast *left;
    struct ast *right;
};

struct list_ast
{
    struct ast *data;
    struct list_ast *next;
};

struct fifo_ast
{
    struct list_ast *head;
    struct list_ast *tail;
    size_t size;
};

struct ast *shuting_yard(struct info *info, struct fifo *file);

struct fifo_ast *fifo_ast_init(void);
size_t fifo_ast_size(struct fifo_ast *fifo_ast);
void fifo_ast_push(struct fifo_ast *fifo_ast, struct ast *elt);
struct ast *fifo_ast_head(struct fifo_ast *fifo_ast);
int fifo_ast_pop(struct fifo_ast *fifo_ast);
int fifo_ast_pop_mais_pas_free(struct fifo_ast *fifo_ast);
void fifo_ast_clear(struct fifo_ast *fifo_ast);
void fifo_ast_destroy(struct fifo_ast *fifo_ast);

struct ast *init_ast(struct token *data);
struct ast *ajout(struct fifo_ast *file, struct token *token);
void ast_print(struct ast *ast);
void ast_destroy(struct ast *ast);

#endif // AST_H

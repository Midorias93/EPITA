#include <stdlib.h>

#include "ast.h"

struct fifo_ast *fifo_ast_init(void)
{
    struct fifo_ast *new_fifo_ast = malloc(sizeof(struct fifo_ast));
    new_fifo_ast->head = NULL;
    new_fifo_ast->tail = NULL;
    new_fifo_ast->size = 0;
    return new_fifo_ast;
}

void fifo_ast_clear(struct fifo_ast *fifo_ast)
{
    while (fifo_ast->head != NULL)
    {
        fifo_ast_pop(fifo_ast);
    }
}

void fifo_ast_destroy(struct fifo_ast *fifo_ast)
{
    if (fifo_ast->size == 0)
    {
        free(fifo_ast);
        return;
    }
    fifo_ast_clear(fifo_ast);
    free(fifo_ast);
}

#include <stdio.h>
#include <stdlib.h>

#include "ast.h"

struct list_ast *list_ast_prepend(struct fifo_ast list, struct ast *ast)
{
    struct list_ast *new_tail = malloc(sizeof(struct list_ast));
    new_tail->data = ast;
    new_tail->next = NULL;
    if (list.tail == NULL)
    {
        return new_tail;
    }
    list.tail->next = new_tail;
    return new_tail;
}

size_t fifo_ast_size(struct fifo_ast *fifo_ast)
{
    return fifo_ast->size;
}

void fifo_ast_push(struct fifo_ast *fifo_ast, struct ast *elt)
{
    if (fifo_ast->size == 0)
    {
        fifo_ast->size++;
        fifo_ast->tail = list_ast_prepend(*fifo_ast, elt);
        fifo_ast->head = fifo_ast->tail;
    }
    else
    {
        fifo_ast->size++;
        fifo_ast->tail = list_ast_prepend(*fifo_ast, elt);
    }
}

struct ast *fifo_ast_head(struct fifo_ast *fifo_ast)
{
    return fifo_ast->head->data;
}

int fifo_ast_pop(struct fifo_ast *fifo_ast)
{
    if (fifo_ast->size == 0)
    {
        return 0;
    }
    else if (fifo_ast->size == 1)
    {
        struct list_ast *retenu = fifo_ast->tail;
        fifo_ast->size--;
        fifo_ast->tail = NULL;
        fifo_ast->head = NULL;
        ast_destroy(retenu->data);
        free(retenu);
    }
    else
    {
        struct list_ast *retenu = fifo_ast->head;
        fifo_ast->size--;
        fifo_ast->head = fifo_ast->head->next;
        ast_destroy(retenu->data);
        free(retenu);
    }
    return 1;
}

int fifo_ast_pop_mais_pas_free(struct fifo_ast *fifo_ast)
{
    if (fifo_ast->size == 0)
    {
        return 0;
    }
    else if (fifo_ast->size == 1)
    {
        struct list_ast *retenu = fifo_ast->tail;
        fifo_ast->size--;
        fifo_ast->tail = NULL;
        fifo_ast->head = NULL;
        free(retenu);
    }
    else
    {
        struct list_ast *retenu = fifo_ast->head;
        fifo_ast->size--;
        fifo_ast->head = fifo_ast->head->next;
        free(retenu);
    }
    return 1;
}

#include <stdio.h>
#include <stdlib.h>

#include "fifo.h"

struct list *list_prepend(struct fifo list, struct token *token)
{
    struct list *new_tail = malloc(sizeof(struct list));
    new_tail->data = token;
    new_tail->next = NULL;
    if (list.tail == NULL)
    {
        return new_tail;
    }
    list.tail->next = new_tail;
    return new_tail;
}

size_t fifo_size(struct fifo *fifo)
{
    return fifo->size;
}

void fifo_push(struct fifo *fifo, struct token *elt)
{
    if (fifo->size == 0)
    {
        fifo->size++;
        fifo->tail = list_prepend(*fifo, elt);
        fifo->head = fifo->tail;
    }
    else
    {
        fifo->size++;
        fifo->tail = list_prepend(*fifo, elt);
    }
}

struct token *fifo_head(struct fifo *fifo)
{
    return fifo->head->data;
}

int fifo_pop(struct fifo *fifo)
{
    if (fifo->size == 0)
    {
        return 0;
    }
    else if (fifo->size == 1)
    {
        struct list *retenu = fifo->tail;
        fifo->size--;
        fifo->tail = NULL;
        fifo->head = NULL;
        free(retenu->data);
        free(retenu);
    }
    else
    {
        struct list *retenu = fifo->head;
        fifo->size--;
        fifo->head = fifo->head->next;
        free(retenu->data);
        free(retenu);
    }
    return 1;
}

int fifo_pop_mais_pas_free(struct fifo *fifo)
{
    if (fifo->size == 0)
    {
        return 0;
    }
    else if (fifo->size == 1)
    {
        struct list *retenu = fifo->tail;
        fifo->size--;
        fifo->tail = NULL;
        fifo->head = NULL;
        free(retenu);
    }
    else
    {
        struct list *retenu = fifo->head;
        fifo->size--;
        fifo->head = fifo->head->next;
        free(retenu);
    }
    return 1;
}

void fifo_print(const struct fifo *fifo)
{
    if (fifo == NULL)
    {
        return;
    }
    struct list *affiche = fifo->head;
    for (size_t i = 0; i < fifo->size; i++)
    {
        print_token(affiche->data);
        affiche = affiche->next;
    }
}

#include <stdio.h>
#include <stdlib.h>

#include "fifo.h"

struct list *list_prepend(struct list *list, int value)
{
    struct list *new_tete = malloc(sizeof(struct list));
    new_tete->data = value;
    new_tete->next = NULL;
    if (list == NULL)
    {
        return new_tete;
    }
    new_tete->next = list;
    return new_tete;
}

size_t fifo_size(struct fifo *fifo)
{
    return fifo->size;
}

void fifo_push(struct fifo *fifo, int elt)
{
    if (fifo->size == 0)
    {
        fifo->size++;
        fifo->tail = list_prepend(fifo->tail, elt);
        fifo->head = fifo->tail;
    }
    else
    {
        fifo->size++;
        fifo->head = list_prepend(fifo->head, elt);
    }
}

int fifo_head(struct fifo *fifo)
{
    return fifo->head->data;
}

void fifo_pop(struct fifo *fifo)
{
    if (fifo->size == 0)
    {
        return;
    }
    else
    {
        struct list *retenu = fifo->head;
        fifo->size--;
        fifo->head = fifo->head->next;
        free(retenu);
    }
}

void fifo_print(const struct fifo *fifo)
{
    struct list *affiche = fifo->head;
    for (size_t i = 0; i < fifo->size; i++)
    {
        printf("%d\n", affiche->data);
        affiche = affiche->next;
    }
}

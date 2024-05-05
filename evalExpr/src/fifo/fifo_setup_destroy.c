#include <stdlib.h>

#include "fifo.h"

struct fifo *fifo_init(void)
{
    struct fifo *new_fifo = malloc(sizeof(struct fifo));
    new_fifo->head = NULL;
    new_fifo->tail = NULL;
    new_fifo->size = 0;
    return new_fifo;
}

void fifo_clear(struct fifo *fifo)
{
    while (fifo->head != fifo->tail)
    {
        fifo_pop(fifo);
    }
    struct list *retenu = fifo->tail;
    fifo->tail = NULL;
    fifo->head = NULL;
    fifo->size = 0;
    free(retenu);
}

void fifo_destroy(struct fifo *fifo)
{
    fifo_clear(fifo);
    free(fifo);
}

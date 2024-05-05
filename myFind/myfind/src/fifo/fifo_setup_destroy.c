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
    while (fifo->head != NULL)
    {
        fifo_pop(fifo);
    }
}

void fifo_destroy(struct fifo *fifo)
{
    if (fifo->size == 0)
    {
        free(fifo);
        return;
    }
    fifo_clear(fifo);
    free(fifo);
}

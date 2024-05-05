#ifndef FIFO_H
#define FIFO_H

#include <stddef.h>
#include "../token/token.h"

struct list
{
    struct token data;
    struct list *next;
};

struct fifo
{
    struct list *head;
    struct list *tail;
    size_t size;
};

struct fifo *fifo_init(void);
size_t fifo_size(struct fifo *fifo);
void fifo_push(struct fifo *fifo, struct token elt);
struct token fifo_head(struct fifo *fifo);
int fifo_pop(struct fifo *fifo);
void fifo_clear(struct fifo *fifo);
void fifo_destroy(struct fifo *fifo);
void fifo_print(const struct fifo *fifo);

#endif /* !FIFO_H */

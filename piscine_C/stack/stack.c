#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

struct stack *stack_push(struct stack *s, int e)
{
    struct stack *tete = malloc(sizeof(struct stack));
    if (tete == NULL)
    {
        return s;
    }
    tete->data = e;
    tete->next = s;
    return tete;
}

struct stack *stack_pop(struct stack *s)
{
    if (s == NULL)
    {
        return NULL;
    }
    struct stack *sauv = s;
    s = s->next;
    free(sauv);
    return s;
}

int stack_peek(struct stack *s)
{
    return s->data;
}

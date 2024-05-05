#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

struct stack *stack_push(struct stack *s, struct token *e)
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
    free(sauv->data);
    free(sauv);
    return s;
}

struct stack *stack_pop_mais_pas_free(struct stack *s)
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

struct token *stack_peek(struct stack *s)
{
    return s->data;
}

void stack_destroy(struct stack *stack)
{
    if (stack == NULL)
    {
        return;
    }
    if (stack->next != NULL)
    {
        stack_destroy(stack->next);
    }
    free(stack->data);
    free(stack);
}

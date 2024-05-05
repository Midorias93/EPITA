#ifndef STACK_H
#define STACK_H

#include "../token/token.h"

struct stack
{
    struct token *data;
    struct stack *next;
};

struct stack *stack_push(struct stack *s, struct token *e);
struct stack *stack_pop(struct stack *s);
struct stack *stack_pop_mais_pas_free(struct stack *s);
struct token *stack_peek(struct stack *s);
void stack_destroy(struct stack *stack);

#endif /* !STACK_H */

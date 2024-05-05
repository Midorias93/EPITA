#include "token.h"

#include <stdlib.h>
#include <stdio.h>

struct token *init_tokent(int val,int type)
{
    struct token *new_token = malloc(sizeof(struct token));
    new_token->data = val;
    new_token->type = type;
    return new_token;
}

void destroy_token(struct token *token)
{
    free(token);
}

void print_token(struct token *token)
{
    if (token->type == 1)
    {
        printf("type = char, val = %c.\n",token->data);
    }
    else
    {
        printf("type = int, val = %d.\n",token->data);
    }
}

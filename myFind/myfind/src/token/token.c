#include "token.h"

struct token *init_token(char *parametre, int type)
{
    struct token *token = malloc(sizeof(struct token));
    if (token == NULL)
    {
        return NULL;
    }
    token->type = type;
    token->parametre = parametre;
    token->negation = 0;
    return token;
}

void print_token(struct token *token)
{
    printf("parametre : %s\n", token->parametre);
    printf("type : %d\n", token->type);
    printf("negation : %d\n", token->negation);
}

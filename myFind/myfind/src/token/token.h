#ifndef TOKEN_H
#define TOKEN_H

#include <stdio.h>
#include <stdlib.h>

enum types
{
    PRINT = 0,
    NAME,
    TYPE,
    NEWER,
    USER,
    GROUP,
    DELETE,
    EXEC,
    EXECP,
    EXECDIR,
    PERM,
    OR,
    AND,
    P_G,
    P_D,
    P_EXCLA,
};

struct token
{
    int type;
    char *parametre;
    int negation;
};

struct token *init_token(char *expression, int type);
void print_token(struct token *token);
void detroy_token(struct token *token);

#endif // TOKEN_H

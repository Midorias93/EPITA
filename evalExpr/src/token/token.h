#ifndef TOKEN_H
#define TOKEN_H

struct token
{
    int data;
    int type;
};

struct token *init_tokent(int val,int type);
void destroy_token(struct token *token);
void print_token(struct token *token);

#endif // TOKEN_H

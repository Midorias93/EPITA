#ifndef FUNCTION_H
#define FUNCTION_H

#include "../ast/ast.h"

struct function
{
    struct function_item *head;
};

struct function_item
{
    char *name;
    struct ast_funcdec *ast;
    struct function_item *next;
};

void add_function(struct function *fnc, struct ast_funcdec *ast, char *word);
void free_function(struct function *fnc);
struct ast_funcdec *search_function(struct function *fnc, char *word);
int pop_function(struct function *fnc, char *word);
struct function *copy_func(struct function *fnc);

#endif /* FUNCTION_H */

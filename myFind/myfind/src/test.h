#ifndef TEST_H
#define TEST_H

#include <dirent.h>

#include "AST/ast.h"
#include "token/token.h"

typedef int (*test)(struct token *, char *path);

int print(struct token *token, char *path);
int name(struct token *token, char *path);
int type(struct token *token, char *path);
int newer(struct token *token, char *path);
int group(struct token *token, char *path);
int user(struct token *token, char *path);
int evaluate(struct ast *ast, char *path, test *list_f);

#endif // TEST_H

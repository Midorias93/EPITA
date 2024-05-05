#ifndef EVALUATE_H
#define EVALUATE_H

#include "../ast/ast.h"
#include "../function/function.h"
#include "../variable/variable.h"

int evaluate(struct ast_input *ast, struct variable *list,
             struct function *fnc);
int evaluate_shellcmd(struct ast_shellcmd *ast, struct variable *list,
                      struct function *fnc, int is_breakable);

#endif /* EVALUATE_H */

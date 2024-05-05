#ifndef PARSER_H
#define PARSER_H

#include "../ast/ast.h"
#include "../function/function.h"
#include "../lexer/lexer.h"

enum parser_status
{
    PARSER_OK,
    PARSER_UNEXPECTED_TOKEN,
};

int number_args(char **args);
enum parser_status parse(struct ast_input **res, struct lexer *lexer);

#endif /* !PARSER_H */

#ifndef TOKEN_H
#define TOKEN_H

#include <unistd.h>

enum token_type
{
    TOKEN_IF, // 'if'
    TOKEN_FI, // 'fi'
    TOKEN_ELIF, // 'elif'
    TOKEN_ELSE, // 'else'
    TOKEN_THEN, // 'then'
    TOKEN_POINTV, // ';'
    TOKEN_NEWLINE, // '\n'
    TOKEN_EOF, // 'eof'
    TOKEN_ERROR, // 'error'
    TOKEN_WORD, // 'word'
    TOKEN_PIPE, // '|'
    TOKEN_NEG, // '!'
    TOKEN_WHILE, // 'while'
    TOKEN_UNTIL, // 'until'
    TOKEN_DO, // 'do'
    TOKEN_DONE, // 'done'
    TOKEN_ANDAND, // '&&'
    TOKEN_OROR, // '||'
    TOKEN_FOR, // 'for'
    TOKEN_IN, // 'in'
    TOKEN_ASSIGNMENT_WORD, // 'x=2'
    TOKEN_REDIRECTION, // '>' | '<' | '>>' | '>&' | '<&' | '>|' | '<>'
    TOKEN_IONUMBER, // 'file descriptor'
    TOKEN_LEFT_BRACKET, // '{'
    TOKEN_RIGHT_BRACKET, // '}'
    TOKEN_LEFT_PAR, // '('
    TOKEN_RIGHT_PAR, // ')'
};

struct token
{
    enum token_type type; // The kind of token
    char *args; // List of arguments
};
#endif /* !TOKEN_H */

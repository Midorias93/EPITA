#ifndef IO_H
#define IO_H

#include <stdio.h>

#include "../lexer/lexer.h"

FILE *io_setup_lexer(const char *path, struct lexer *lexer);
int io_getline(struct lexer *lexer);
void io_close(FILE *stream);

#endif // IO_H

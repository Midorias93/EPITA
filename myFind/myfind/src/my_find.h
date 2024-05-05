#ifndef MY_FIND_H
#define MY_FIND_H

#include "AST/ast.h"
#include "action.h"
#include "info.h"
#include "test.h"

int donne_type(char *type);
int possed_un_argument(int type);
struct fifo *fait_la_file(struct info *info, int argc, char *argv[]);

#endif // MY_FIND_H

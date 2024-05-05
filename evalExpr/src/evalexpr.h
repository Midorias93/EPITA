#ifndef EVALXPR_H
#define EVALXPR_H

#include <stdio.h>
#include <stdlib.h>
#include "stack/stack.h"
#include "fifo/fifo.h"
#include "token/token.h"
#include "evalexpr.h"

int is_rpn(char *str);
struct fifo *pars(char *expression);
int calcul_rpn(struct fifo *file, int *error);
struct fifo *convert_standar(struct fifo *file, int *error);

#endif // EVALXPR_H

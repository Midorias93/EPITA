#ifndef EXPANSION_H
#define EXPANSION_H

#include "../variable/variable.h"

int my_expand(char *args[], struct variable *list_variable);
int expand_manager(char **args, int size, struct variable *list_variable);

#endif // EXPANSION_H

#ifndef BUILTIN_H
#define BUILTIN_H

#include "../function/function.h"
#include "../variable/variable.h"

int my_echo(char **arg, int nb);
int my_true(void);
int my_false(void);
int my_cd(char *args[], int nb_args, struct variable *var);
int my_break(char *args[], struct variable *var);
int my_continue(char *args[], struct variable *var);
int my_unset(char **args, int nb_args, struct variable *var,
             struct function *fnc);
int my_exit(char *args[], struct variable *var);

#endif /* BUILTIN_H */

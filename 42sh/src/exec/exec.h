#ifndef EXEC_H
#define EXEC_H

#include "../function/function.h"
#include "../variable/variable.h"

int my_exec(struct variable *var, char *args[], struct function *fnc);
int get_correct_value(int nb);
int is_continue(int nb);
int is_break(int nb);

enum builtin
{
    FALSE = 0,
    TRUE,
    ECHO,
    CD,
    UNSET,
    AUTRE,
    EXIT = 500,
    BREAK_TO_END = 501,
    BREAK = 502, // pair
    CONTINUE = 503 // impair
};

#endif /* EXEC_H */

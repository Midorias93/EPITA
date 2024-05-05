#include "../exec/exec.h"

#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "../builtin/builtin.h"
#include "../evaluate/evaluate.h"
#include "../parser/parser.h"
#include "../variable/variable.h"

static int number_length(long int value)
{
    int i = 2;
    while (value > 0)
    {
        value /= 10;
        i++;
    }

    return i;
}

int is_break(int nb)
{
    if (nb > 501)
    {
        return (nb % 2 == 0);
    }
    return 0;
}

int is_continue(int nb)
{
    if (nb > 501)
    {
        return (nb % 2 == 1);
    }
    return 0;
}

int get_correct_value(int nb)
{
    if (nb > 501)
    {
        nb -= 2;
        if (nb <= 501)
            return 0;
    }
    return nb;
}

static int exec_echo(struct variable *var, char *args[])
{
    int value = my_echo(args, number_args(args) - 1);
    char *str = malloc(number_length(value));
    special_append(var, "?", my_itoa(value, str));
    free(str);
    return value;
}

static int exec_true(struct variable *var)
{
    special_append(var, "?", "0");
    return my_true();
}

static int exec_false(struct variable *var)
{
    special_append(var, "?", "1");
    return my_false();
}

static int exec_cd(struct variable *var, char *args[])
{
    int value = my_cd(args, number_args(args) - 1, var);
    char *str = malloc(number_length(value));
    special_append(var, "?", my_itoa(value, str));
    free(str);
    return value;
}

static int is_it_a_builtin_and_exec_this_builtin(struct variable *var,
                                                 char *args[],
                                                 struct function *fnc)
{
    if (!strcmp(args[0], "true"))
        return exec_true(var);
    if (!strcmp(args[0], "false"))
        return exec_false(var);
    if (!strcmp(args[0], "echo"))
        return exec_echo(var, args);
    if (!strcmp(args[0], "cd"))
        return exec_cd(var, args);
    if (!strcmp(args[0], "break"))
        return my_break(args, var);
    if (!strcmp(args[0], "continue"))
        return my_continue(args, var);
    if (!strcmp(args[0], "exit"))
        return my_exit(args, var);
    if (!strcmp(args[0], "unset"))
        return my_unset(args, number_args(args) - 1, var, fnc);
    else
    {
        return -1;
    }
}

int my_exec(struct variable *var, char *args[], struct function *fnc)
{
    struct ast_funcdec *ast = search_function(fnc, args[0]);
    if (ast)
    {
        int value = evaluate_shellcmd(ast->child, var, fnc, 0);
        special_append(var, "?", "0");
        return value;
    }
    int value = is_it_a_builtin_and_exec_this_builtin(var, args, fnc);
    if (value == -1)
    {
        int pid = fork();
        if (pid == -1)
        {
            fprintf(stderr, "exec: failed\n");
            return 1;
        }
        if (pid == 0)
        {
            int statuscode = execvp(args[0], args);
            if (statuscode == -1)
                _exit(127);
        }

        int status;
        waitpid(pid, &status, 0);

        int return_value = 1;

        if (WIFEXITED(status))
        {
            return_value = WEXITSTATUS(status);
        }

        char *str = malloc(number_length(return_value));
        special_append(var, "?", my_itoa(return_value, str));
        free(str);

        if (return_value == 127)
        {
            fprintf(stderr, "exec: %s failed\n", args[0]);
            return -127;
        }

        return return_value;
    }
    else
    {
        return value;
    }
}

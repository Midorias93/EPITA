#include "../builtin/builtin.h"

#include <dirent.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include "../exec/exec.h"
#include "../function/function.h"
#include "../variable/variable.h"

struct option
{
    int n;
    int e;
};

static void my_print(char *args, struct option option)
{
    size_t size_args = strlen(args);
    for (size_t i = 0; i < size_args; i++)
    {
        if (option.e == 1)
        {
            if (args[i] == '\\')
            {
                if (i + 1 != size_args && args[i + 1] == 'n')
                {
                    putchar('\n');
                    i++;
                }

                else if (i + 1 != size_args && args[i + 1] == '\\')
                {
                    putchar('\\');
                    i++;
                }

                else if (i + 1 != size_args && args[i + 1] == 't')
                {
                    putchar('\t');
                    i++;
                }

                else
                    putchar(args[i]);
            }
            else
                putchar(args[i]);
        }
        else
            putchar(args[i]);
    }
}

int my_echo(char **args, int nb_args)
{
    struct option option;
    option.n = 0;
    option.e = 0;
    int is_option = 1;
    for (int i = 1; i < nb_args; i++)
    {
        if (args[i][0] == '-' && is_option == 1)
        {
            struct option option_tmp;
            option_tmp.e = option.e;
            option_tmp.n = option.n;
            for (size_t j = 1; j < strlen(args[i]); j++)
            {
                if (args[i][j] == 'n')
                    option_tmp.n = 1;

                else if (args[i][j] == 'e')
                    option_tmp.e = 1;

                else if (args[i][j] == 'E')
                    option_tmp.e = 0;

                else
                {
                    is_option = 0;
                    break;
                }
            }

            if (is_option == 1)
            {
                option.e = option_tmp.e;
                option.n = option_tmp.n;
            }
            else
            {
                my_print(args[i], option);
                if (i != nb_args - 1)
                    printf(" ");
            }
        }

        else
        {
            my_print(args[i], option);
            if (i != nb_args - 1)
                printf(" ");
        }
    }
    if (option.n == 0)
        putchar('\n');

    return 0;
}

static int is_number(char *str)
{
    int i = 0;
    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return 0;
        i++;
    }
    return 1;
}

int my_continue(char *args[], struct variable *var)
{
    int nb = 0;
    while (args[nb])
        nb++;
    if (nb > 1 && !is_number(args[1]))
    {
        fprintf(stderr, "42sh: break : non numerical arguments given\n");
        special_append(var, "?", "128");
        return EXIT;
    }
    if (nb > 2)
    {
        special_append(var, "?", "1");
        fprintf(stderr, "42sh: break :too many arguments\n");
        return EXIT;
    }
    if (nb == 1)
    {
        special_append(var, "?", "0");
        return CONTINUE;
    }
    int n = atoi(args[1]);
    if (n == 0)
    {
        fprintf(stderr, "42sh: break: loop count of range\n");
        special_append(var, "?", "1");
        return BREAK_TO_END;
    }
    special_append(var, "?", "0");
    return CONTINUE + (n - 1) * 2;
}

int my_break(char *args[], struct variable *var)
{
    int nb = 0;
    while (args[nb])
        nb++;
    if (nb > 1 && !is_number(args[1]))
    {
        fprintf(stderr, "42sh: break : non numerical arguments given\n");
        special_append(var, "?", "128");
        return EXIT;
    }
    if (nb > 2)
    {
        special_append(var, "?", "1");
        fprintf(stderr, "42sh: break :too many arguments\n");
        return EXIT;
    }
    if (nb == 1)
    {
        special_append(var, "?", "0");
        return BREAK;
    }
    int n = atoi(args[1]);
    if (n == 0)
    {
        fprintf(stderr, "42sh: break: loop count of range\n");
        special_append(var, "?", "1");
        return BREAK_TO_END;
    }
    special_append(var, "?", "0");
    return BREAK + (n - 1) * 2;
}

int my_exit(char *args[], struct variable *var)
{
    int nb = 0;
    while (args[nb])
        nb++;
    if (nb > 1 && !is_number(args[1]))
    {
        fprintf(stderr, "42sh: exit : non numerical arguments given\n");
        special_append(var, "?", "2");
        return EXIT;
    }
    if (nb > 2)
    {
        special_append(var, "?", "1");
        fprintf(stderr, "42sh: break :too many arguments\n");
        return EXIT;
    }
    if (nb == 1)
    {
        special_append(var, "?", "0");
        return EXIT;
    }
    int n = atoi(args[1]) % 256;
    char str_return[16] = { 0 };
    special_append(var, "?", my_itoa(n, str_return));
    return EXIT;
}

int my_true(void)
{
    return 0;
}

int my_false(void)
{
    return 1;
}

int my_unset(char **args, int nb_args, struct variable *var,
             struct function *fnc)
{
    int i = 1;
    while (i < nb_args)
    {
        if (!strcmp(args[i], "-f"))
        {
            i++;
            if (!strcmp(args[i], "-v"))
            {
                special_append(var, "?", "1");
                fprintf(stderr,
                        "42sh: unset: cannot unset variable and function at "
                        "the same time");
                return 1;
            }
            pop_function(fnc, args[i]);
        }
        else if (!strcmp(args[i], "-v"))
        {
            i++;
            if (!strcmp(args[i], "-f"))
            {
                special_append(var, "?", "1");
                fprintf(stderr,
                        "42sh: unset: cannot unset variable and function at "
                        "the same time");
                return 1;
            }
            pop_variable(var, args[i]);
        }
        else
        {
            if (!pop_variable(var, args[i]))
                pop_function(fnc, args[i]);
        }
        i++;
    }
    return 0;
}

int my_cd(char *args[], int nb_args, struct variable *var)
{
    if (nb_args > 2)
    {
        fprintf(stderr, "42sh: cd to much arguments\n");
        return 1;
    }

    DIR *fd = opendir(args[1]);
    if (fd == NULL && *args[1] != '-')
    {
        fprintf(stderr, "42sh: cd dir does not exist\n");
        return 1;
    }

    closedir(fd);

    if (!strcmp(args[1], "-"))
    {
        char *old_path = give_variable(var, "PWD", 3);
        char *save = malloc((strlen(old_path) + 1) * sizeof(char));
        strcpy(save, old_path);

        old_path = give_variable(var, "OLDPWD", 6);
        special_append(var, "PWD", old_path);

        chdir(old_path);

        printf("%s\n", old_path);

        special_append(var, "OLDPWD", save);
        free(save);
    }
    else
    {
        special_append(var, "OLDPWD", give_variable(var, "PWD", 3));
        chdir(args[1]);
        char pwd[4096] = { 0 };
        getcwd(pwd, 4096);
        special_append(var, "PWD", pwd);
    }
    return 0;
}

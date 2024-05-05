#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../parser/parser.h"
#include "../variable/variable.h"

static void swap2end(char *args, int *nb_signe, int word_pos, int size)
{
    for (int i = word_pos; i + *nb_signe < size - 1; i++)
    {
        char swap = args[i];
        args[i] = args[i + 1];
        args[i + 1] = swap;
    }
    *nb_signe += 1;
    args[size - *nb_signe] = 0;
}

static int is_special_for_double_quote(char test)
{
    if (test == '$' || test == '`' || test == '"' || test == '\\'
        || test == '\n')
        return 1;
    return 0;
}

int expand_manager(char **args, int size, struct variable *list_variable)
{
    int word_pos = 0;
    int nb_signe = 0;
    while (word_pos + nb_signe < size)
    {
        if ((*args)[word_pos] == '\\')
        {
            swap2end(*args, &nb_signe, word_pos, size);
            word_pos++;
        }
        else if ((*args)[word_pos] == '\'')
        {
            int save_quote = word_pos++;
            while (word_pos + nb_signe <= size)
            {
                if ((*args)[word_pos] == '\'')
                {
                    swap2end(*args, &nb_signe, word_pos, size);
                    swap2end(*args, &nb_signe, save_quote, size);
                    word_pos--;
                    break;
                }
                else
                {
                    word_pos++;
                }
            }
        }
        else if ((*args)[word_pos] == '\"')
        {
            // FIXME : it is just a copy-paste of above
            int save_quote = word_pos++;
            while (word_pos + nb_signe < size)
            {
                if ((*args)[word_pos] == '\"')
                {
                    swap2end(*args, &nb_signe, word_pos, size);
                    swap2end(*args, &nb_signe, save_quote, size);
                    word_pos--;
                    break;
                }
                else if ((*args)[word_pos] == '$')
                {
                    // cas '$'
                    // FIXME
                    size = variable_expander(args, &word_pos, list_variable);
                    nb_signe = 0;
                }
                else if ((*args)[word_pos] == '\\'
                         && is_special_for_double_quote((*args)[word_pos + 1]))
                {
                    // cas '\'
                    word_pos += 2;
                }
                else
                {
                    word_pos++;
                }
            }
        }
        else if ((*args)[word_pos] == '$')
        {
            // cas '$'
            // FIXME
            size = variable_expander(args, &word_pos, list_variable);
            nb_signe = 0;
        }
        else
        {
            word_pos++;
        }
    }
    return 0;
}

int my_expand(char *args[], struct variable *list_variable)
{
    int size_args = number_args(args) - 1;
    for (int i = 0; i < size_args; i++)
    {
        int len = strlen(args[i]);
        expand_manager(&args[i], len, list_variable);
    }
    return 0;
}

/* Old Version of expand manager working with 2 function

static int backslash_manager(char *args, int size)
{
    int word_pos = 0;
    int nb_backslash = 0;
    while (word_pos + nb_backslash <= size)
    {
        if (args[word_pos] == '\\')
        {
            for (int i = word_pos; i + nb_backslash < size; i++)
            {
                char swap = args[i];
                args[i] = args[i + 1];
                args[i + 1] = swap;
            }
            nb_backslash++;
        }
        else
        {
            if (args[word_pos] == '\'')
            {
                word_pos++;
                while (args[word_pos] != '\'')
                {
                    word_pos++;
                }
            }
            else if (args[word_pos] == '"')
            {
                word_pos++;
                while (args[word_pos] != '"')
                {
                    word_pos++;
                }
            }
        }
        word_pos++;
    }
    return 0;
}

// FIXME: creer fonction swap
static int quoting_manager(char *args, int size)
{
    int word_pos = 0;
    int nb_quote = 0;
    while (word_pos + nb_quote <= size)
    {
        if (args[word_pos] == '\'')
        {
            int save_quote = word_pos++;
            while (word_pos + nb_quote <= size)
            {
                if (args[word_pos] == '\'')
                {
                    for (int i = word_pos; i + nb_quote < size; i++)
                    {
                        char swap = args[i];
                        args[i] = args[i + 1];
                        args[i + 1] = swap;
                    }
                    nb_quote++;
                    for (int i = save_quote; i + nb_quote < size; i++)
                    {
                        char swap = args[i];
                        args[i] = args[i + 1];
                        args[i + 1] = swap;
                    }
                    nb_quote++;
                    word_pos--;
                    break;
                }
                else
                {
                    word_pos++;
                }
            }
        }
        else if (args[word_pos] == '"')
        {
            int save_quote = word_pos++;
            while (word_pos + nb_quote <= size)
            {
                if (args[word_pos] == '"')
                {
                    for (int i = word_pos; i + nb_quote < size; i++)
                    {
                        char swap = args[i];
                        args[i] = args[i + 1];
                        args[i + 1] = swap;
                    }
                    nb_quote++;
                    for (int i = save_quote; i + nb_quote < size; i++)
                    {
                        char swap = args[i];
                        args[i] = args[i + 1];
                        args[i + 1] = swap;
                    }
                    nb_quote++;
                    word_pos--;
                    break;
                }
                else
                {
                    word_pos++;
                }
            }
        }
        else
        {
            word_pos++;
        }
    }
    return 0;
}
*/

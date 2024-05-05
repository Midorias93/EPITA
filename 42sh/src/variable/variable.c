#include "variable.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "../expansion/expansion.h"

char *my_itoa(long int value, char *s)
{
    int x = 0;
    char inter = 0;
    int k = 1;
    long dix = 10;
    while (dix <= value)
    {
        k++;
        dix *= 10;
    }
    dix /= 10;
    for (int i = x; i < k + x; i++)
    {
        inter = value / dix;
        s[i] = inter + '0';
        value -= dix * inter;
        dix /= 10;
    }
    s[k + x] = '\0';
    return s;
}

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

struct pair_list *special_append(struct variable *var, char *key,
                                 char *value) // Not malloc
{
    size_t len_key = strlen(key);
    size_t len_value = strlen(value);
    char *new_assignment = malloc(sizeof(char) * (len_value + len_key + 2));
    strcpy(new_assignment, key);
    strcat(new_assignment, "=");
    strcat(new_assignment, value);
    struct pair_list *new_list = append_variable(var, new_assignment);
    free(new_assignment);
    return new_list;
}

void argument_variable(struct variable *var, char *argv[], int argc, int pos)
{
    for (int i = 1; i < argc - pos; i++)
    {
        char *str = calloc(number_length(i) + 1, sizeof(char));
        special_append(var, my_itoa(i, str), argv[i + pos]);
        free(str);
    }
}

struct variable *init_variable(void)
{
    struct variable *var = malloc(sizeof(struct variable));

    var->head = NULL;

    // PWD
    // OLDPWD
    char oldcwd[4096] = { 0 };
    getcwd(oldcwd, sizeof(oldcwd));
    special_append(var, "OLDPWD", oldcwd);
    special_append(var, "PWD", oldcwd);
    // IFS
    special_append(var, "IFS", " \t\n");
    // PID
    long int pid = getpid();
    char pid_char[4096] = { 0 };
    special_append(var, "$", my_itoa(pid, pid_char));
    // UID
    unsigned int uid = getuid();
    char uid_char[4096] = { 0 };
    special_append(var, "UID", my_itoa(uid, uid_char));

    return var;
}

struct pair_list *append_variable(struct variable *var, char *ass_word)
{
    struct pair_list *list = var->head;
    int len = strlen(ass_word);
    int i = 0;
    while (ass_word[i] != '=')
    {
        i++;
    }
    char *key = calloc(i + 1, sizeof(char));
    key = strncpy(key, ass_word, i);
    char *value = calloc(len - i, sizeof(char));
    value = strncpy(value, ass_word + i + 1, len - i - 1);
    expand_manager(&value, len - i - 1, var);

    struct pair_list *new_ass = NULL;

    if (list && !strncmp(key, list->key, i + 1))
    {
        new_ass = list;
        free(new_ass->value);
        free(new_ass->key);
    }
    else
    {
        new_ass = calloc(1, sizeof(struct pair_list));
        new_ass->next = list;

        struct pair_list *actual = list;
        struct pair_list *save = NULL;
        while (actual && actual->next)
        {
            if (!strncmp(key, actual->next->key, i + 1))
            {
                save = actual->next->next;
                free(actual->next->key);
                free(actual->next->value);
                free(actual->next);
                actual->next = save;
                break;
            }
            actual = actual->next;
        }
    }

    new_ass->key = key;
    new_ass->value = value;
    var->head = new_ass;
    return new_ass;
}

int pop_variable(struct variable *var, char *key)
{
    struct pair_list *save = NULL;
    if (!strcmp(var->head->key, key))
    {
        save = var->head->next;
        free(var->head->key);
        free(var->head->value);
        free(var->head);
        var->head = save;
        return 1;
    }
    struct pair_list *actual = var->head;
    while (actual && actual->next)
    {
        if (!strcmp(key, actual->next->key))
        {
            save = actual->next->next;
            free(actual->next->key);
            free(actual->next->value);
            free(actual->next);
            actual->next = save;
            return 1;
        }
        actual = actual->next;
    }
    return 0;
}

static void free_list(struct pair_list *list)
{
    if (!list)
        return;
    if (list->next)
        free_list(list->next);
    free(list->key);
    free(list->value);
    free(list);
}

void free_variable(struct variable *sentinel)
{
    if (!sentinel)
        return;
    if (sentinel->head)
        free_list(sentinel->head);
    free(sentinel);
}

char *give_variable(struct variable *var, char *key, size_t len)
{
    struct pair_list *list = var->head;
    if (!list)
        return NULL;
    if (!strncmp(key, "RANDOM", 7))
    {
        char *aleatoire = calloc(16, sizeof(char));
        int alea = rand() / 100000;
        srand(rand());
        my_itoa(alea, aleatoire);
        return aleatoire;
    }
    while (list)
    {
        if (!strncmp(key, list->key, len + 1))
        {
            return list->value;
        }
        list = list->next;
    }
    return NULL;
}

static int variable_expander_2(char **word, int *word_pos,
                               struct var_exp_struct *ves)
{
    int i = ves->i;
    int len_init = ves->len_init;
    char *key = ves->key;
    char *value = ves->value;
    char *new_word = NULL;
    if (key == NULL)
    {
        *word_pos += 1;
        free(ves);
        return len_init;
    }
    if (value == NULL)
    {
        new_word = calloc(len_init - i, sizeof(char));
        strncpy(new_word, *word, *word_pos);
        strcpy(new_word + *word_pos, (*word) + *word_pos + i + 1);
        free(*word);
        *word = new_word;
        if (!strncmp(key, "RANDOM", 7))
            free(value);
        free(key);
        free(ves);
        return len_init - i;
    }
    else
    {
        int len_value = strlen(value);
        new_word = calloc(len_init - i + len_value, sizeof(char));
        strncpy(new_word, *word, *word_pos);
        strcpy(new_word + *word_pos, value);
        strcpy(new_word + *word_pos + len_value, (*word) + *word_pos + i + 1);
        free(*word);
        *word = new_word;
        *word_pos = *word_pos + len_value;
        if (!strncmp(key, "RANDOM", 7))
            free(value);
        free(key);
        free(ves);
        return len_init - i + len_value;
    }
}

int variable_expander(char **word, int *word_pos, struct variable *var)
{
    int len_init = strlen(*word);
    int i = 1;
    char *key = NULL;
    char *value = NULL;
    if (*word_pos + i < len_init && (*word)[*word_pos + i] == '{')
    {
        while ((*word)[*word_pos + ++i] != '}')
            ;
        key = calloc(i - 1, sizeof(char));
        strncpy(key, (*word) + *word_pos + 2, i - 2);
        value = give_variable(var, key, i - 2);
    }
    else if (*word_pos + i < len_init
             && (isalpha((*word)[*word_pos + i])
                 || (*word)[*word_pos + i] == '_'))
    {
        while (*word_pos + i < len_init
               && (isalnum((*word)[*word_pos + i + 1])
                   || (*word)[*word_pos + i + 1] == '_'))
        {
            i++;
        }
        key = calloc(i + 1, sizeof(char));
        strncpy(key, (*word) + *word_pos + 1, i);
        value = give_variable(var, key, i);
    }
    else if (*word_pos + i < len_init
             && (isdigit((*word)[*word_pos + i])
                 || (*word)[*word_pos + i] == '$'
                 || (*word)[*word_pos + i] == '?'))
    {
        key = calloc(i + 1, sizeof(char));
        strncpy(key, (*word) + *word_pos + 1, i);
        value = give_variable(var, key, i);
    }

    struct var_exp_struct *ves = malloc(sizeof(struct var_exp_struct));
    ves->i = i;
    ves->len_init = len_init;
    ves->key = key;
    ves->value = value;

    return variable_expander_2(word, word_pos, ves);
}

struct variable *copy_var(struct variable *var)
{
    struct variable *new = calloc(1, sizeof(struct variable));

    struct pair_list *tmp = var->head;
    while (tmp != NULL)
    {
        special_append(new, tmp->key, tmp->value);
        tmp = tmp->next;
    }

    return new;
}

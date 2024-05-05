#ifndef VARIABLE_H
#define VARIABLE_H

#include <stddef.h>

struct pair_list
{
    char *key;
    char *value;
    struct pair_list *next;
};

struct variable
{
    struct pair_list *head;
};

struct var_exp_struct
{
    int len_init;
    int i;
    char *key;
    char *value;
};

struct variable *init_variable(void);
/* Add a variable to list
 * Return the new head of the list
 * Act like a stack                 */
void free_variable(struct variable *sentinel);
struct pair_list *append_variable(struct variable *var, char *ass_word);
struct pair_list *special_append(struct variable *var, char *key, char *value);
char *give_variable(struct variable *var, char *key, size_t len);
int variable_expander(char **word, int *word_pos, struct variable *var);
char *my_itoa(long int value, char *s);
int pop_variable(struct variable *var, char *key);
void argument_variable(struct variable *var, char *argv[], int argc, int pos);
struct variable *copy_var(struct variable *var);

#endif /* !VARIABLE_H */

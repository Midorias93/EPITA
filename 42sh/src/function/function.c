#include "function.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void add_function(struct function *fnc, struct ast_funcdec *ast, char *word)
{
    struct function_item *tmp = malloc(sizeof(struct function_item));
    tmp->name = word;
    tmp->ast = ast;
    tmp->next = NULL;

    struct function_item *curr = fnc->head;
    if (curr == NULL)
        fnc->head = tmp;

    else
    {
        while (curr->next != NULL)
            curr = curr->next;

        curr->next = tmp;
    }
}

int pop_function(struct function *fnc, char *word)
{
    struct function_item *save = NULL;

    if (!strcmp(fnc->head->name, word))
    {
        save = fnc->head->next;
        free_shellcmd(fnc->head->ast->child);
        free(fnc->head->ast->word);
        free(fnc->head->ast);
        free(fnc->head);

        fnc->head = save;
        return 1;
    }

    struct function_item *curr = fnc->head;
    while (curr && curr->next)
    {
        if (!strcmp(word, curr->next->name))
        {
            save = curr->next->next;
            free_shellcmd(curr->next->ast->child);
            free(curr->next->ast->word);
            free(curr->next->ast);
            free(curr->next);

            curr->next = save;
            return 1;
        }
        curr = curr->next;
    }
    return 0;
}

void free_function(struct function *fnc)
{
    struct function_item *curr = fnc->head;

    while (curr != NULL)
    {
        struct function_item *tmp = curr->next;
        free_shellcmd(curr->ast->child);
        free(curr->ast->word);
        free(curr->ast);
        free(curr);
        curr = tmp;
    }

    free(fnc);
}

struct ast_funcdec *search_function(struct function *fnc, char *word)
{
    struct function_item *curr = fnc->head;

    while (curr != NULL)
    {
        if (!strcmp(curr->name, word))
            return curr->ast;

        curr = curr->next;
    }

    return NULL;
}

struct function *copy_func(struct function *fnc)
{
    struct function *new = calloc(1, sizeof(struct function));

    struct function_item *tmp = fnc->head;
    while (tmp != NULL)
    {
        add_function(new, tmp->ast, tmp->name);
        tmp = tmp->next;
    }

    return new;
}

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

struct list *list_prepend(struct list *list, int value)
{
    struct list *L_p = malloc(sizeof(struct list));
    if (L_p == NULL)
    {
        return NULL;
    }
    if (list == NULL)
    {
        L_p->data = value;
        L_p->next = NULL;
        return L_p;
    }
    L_p->data = value;
    L_p->next = list;
    return L_p;
}

size_t list_length(struct list *list)
{
    if (list == NULL)
    {
        return 0;
    }
    if (list->next == NULL)
    {
        return 1;
    }
    return 1 + list_length(list->next);
}

void list_print(struct list *list)
{
    if (list == NULL)
    {
        return;
    }
    if (list->next == NULL)
    {
        printf("%d\n", list->data);
        return;
    }
    else
    {
        printf("%d ", list->data);
        list_print(list->next);
    }
}

void list_destroy(struct list *list)
{
    if (list == NULL)
    {
        return;
    }
    if (list->next == NULL)
    {
        free(list);
        return;
    }
    list_destroy(list->next);
    free(list);
}

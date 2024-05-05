#include "list.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

struct list *list_prepend(struct list *list, const void *value,
                          size_t data_size)
{
    struct list *n_list = malloc(sizeof(struct list));
    if (n_list == NULL)
    {
        return NULL;
    }
    n_list->data = malloc(data_size);
    n_list->data = memcpy(n_list->data, value, data_size);
    n_list->next = list;
    return n_list;
}

size_t list_length(struct list *list)
{
    size_t taille = 1;
    if (list == NULL)
    {
        return 0;
    }
    while (list->next != NULL)
    {
        taille++;
        list = list->next;
    }
    return taille;
}

void list_destroy(struct list *list)
{
    if (list == NULL)
    {
        return;
    }
    if (list->next != NULL)
    {
        list_destroy(list->next);
    }
    free(list->data);
    free(list);
}

#include <stdio.h>

#include "dlist.h"

void dlist_print(const struct dlist *list)
{
    if (list->size == 0)
    {
        return;
    }
    struct dlist_item *p_elt = list->head;
    while (p_elt != list->tail)
    {
        printf("%d\n", p_elt->data);
        p_elt = p_elt->next;
    }
    printf("%d\n", p_elt->data);
}

size_t dlist_size(const struct dlist *list)
{
    return list->size;
}

int dlist_get(const struct dlist *list, size_t index)
{
    if (index >= list->size)
    {
        return -1;
    }
    else
    {
        if (index < list->size / 2)
        {
            struct dlist_item *p_elt = list->head;
            for (size_t i = 0; i < index; i++)
            {
                p_elt = p_elt->next;
            }
            return p_elt->data;
        }
        else
        {
            struct dlist_item *p_elt = list->tail;
            for (size_t i = list->size - 1; i > index; i--)
            {
                p_elt = p_elt->prev;
            }
            return p_elt->data;
        }
    }
}

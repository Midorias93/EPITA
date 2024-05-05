#include <stdlib.h>

#include "dlist.h"

struct dlist *dlist_init(void)
{
    struct dlist *new_dlist = malloc(sizeof(struct dlist));
    if (new_dlist == NULL)
    {
        return NULL;
    }
    new_dlist->size = 0;
    new_dlist->head = NULL;
    new_dlist->tail = NULL;
    return new_dlist;
}

static int dlist_pop_front(struct dlist *list)
{
    if (list->size == 0)
    {
        return 0;
    }
    if (list->size == 1)
    {
        struct dlist_item *save = list->head;
        list->head = NULL;
        list->tail = NULL;
        free(save);
        list->size--;
        return 1;
    }
    else
    {
        struct dlist_item *save = list->head;
        list->head = list->head->next;
        list->head->prev = NULL;
        free(save);
    }
    list->size--;
    return 1;
}

void dlist_clear(struct dlist *list)
{
    while (dlist_pop_front(list))
    {}
}

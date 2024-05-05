#include <stdlib.h>

#include "dlist.h"

void dlist_map_square(struct dlist *list)
{
    if (list->size == 0)
    {
        return;
    }
    struct dlist_item *p_elt = list->head;
    while (p_elt != list->tail)
    {
        p_elt->data = p_elt->data * p_elt->data;
        p_elt = p_elt->next;
    }
    p_elt->data = p_elt->data * p_elt->data;
}

static void swap_data(int *a, int *b)
{
    int save = *a;
    *a = *b;
    *b = save;
}

void dlist_reverse(struct dlist *list)
{
    struct dlist_item *p_head = list->head;
    struct dlist_item *p_tail = list->tail;
    for (size_t i = 0; i < list->size / 2; i++)
    {
        swap_data(&p_head->data, &p_tail->data);
        p_head = p_head->next;
        p_tail = p_tail->prev;
    }
}

static int dlist_pop_back(struct dlist *list)
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
        struct dlist_item *save = list->tail;
        list->tail = list->tail->prev;
        list->tail->next = NULL;
        free(save);
    }
    list->size--;
    return 1;
}

struct dlist *dlist_split_at(struct dlist *list, size_t index)
{
    if (index > list->size)
    {
        return NULL;
    }
    struct dlist *part_2 = dlist_init();
    if (list->size == 0)
    {
        return dlist_init();
    }
    else
    {
        size_t taille = list->size;
        for (size_t i = 0; i < taille - index; i++)
        {
            dlist_push_front(part_2, list->tail->data);
            dlist_pop_back(list);
        }
        return part_2;
    }
}

void dlist_concat(struct dlist *list1, struct dlist *list2)
{
    struct dlist_item *p_elt = list2->head;
    for (size_t i = 0; i < list2->size; i++)
    {
        dlist_push_back(list1, p_elt->data);
        p_elt = p_elt->next;
    }
    dlist_clear(list2);
}

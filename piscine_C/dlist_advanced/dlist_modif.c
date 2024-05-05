#include <stdlib.h>

#include "dlist.h"

static struct dlist_item *dlist_item_init(int elt)
{
    struct dlist_item *ndl_item = malloc(sizeof(struct dlist_item));
    if (ndl_item == NULL)
    {
        return NULL;
    }
    ndl_item->data = elt;
    ndl_item->next = NULL;
    ndl_item->prev = NULL;
    return ndl_item;
}

int dlist_push_front(struct dlist *list, int element)
{
    if (element < 0)
    {
        return 0;
    }
    struct dlist_item *ndl_item = dlist_item_init(element);
    if (ndl_item == NULL)
    {
        return 0;
    }
    if (list->size == 0)
    {
        list->head = ndl_item;
        list->tail = ndl_item;
    }
    else
    {
        list->head->prev = ndl_item;
        ndl_item->next = list->head;
        list->head = ndl_item;
    }
    list->size++;
    return 1;
}

int dlist_push_back(struct dlist *list, int element)
{
    if (element < 0)
    {
        return 0;
    }
    struct dlist_item *ndl_item = dlist_item_init(element);
    if (ndl_item == NULL)
    {
        return 0;
    }
    if (list->size == 0)
    {
        list->head = ndl_item;
        list->tail = ndl_item;
    }
    else
    {
        list->tail->next = ndl_item;
        ndl_item->prev = list->tail;
        list->tail = ndl_item;
    }
    list->size++;
    return 1;
}

static void swap_data(int *a, int *b)
{
    int save = *a;
    *a = *b;
    *b = save;
}

int dlist_insert_at(struct dlist *list, int element, size_t index)
{
    if (index > list->size)
    {
        return -1;
    }
    if (index < list->size / 2)
    {
        if (dlist_push_front(list, element))
        {
            struct dlist_item *p_elt = list->head;
            for (size_t i = 0; i < index; i++)
            {
                swap_data(&p_elt->data, &p_elt->next->data);
                p_elt = p_elt->next;
            }
        }
        else
        {
            return -1;
        }
    }
    else
    {
        if (dlist_push_back(list, element))
        {
            struct dlist_item *p_elt = list->tail;
            for (size_t i = list->size - 1; i > index; i--)
            {
                swap_data(&p_elt->data, &p_elt->prev->data);
                p_elt = p_elt->prev;
            }
        }
        else
        {
            return -1;
        }
    }
    return 1;
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

static struct dlist_item *get_pointeur(struct dlist *list, size_t index)
{
    if (index < list->size / 2)
    {
        struct dlist_item *p_elt = list->head;
        for (size_t i = 0; i < index; i++)
        {
            p_elt = p_elt->next;
        }
        return p_elt;
    }
    else
    {
        struct dlist_item *p_elt = list->tail;
        for (size_t i = list->size - 1; i > index; i--)
        {
            p_elt = p_elt->prev;
        }
        return p_elt;
    }
}

int dlist_remove_at(struct dlist *list, size_t index)
{
    if (index >= list->size)
    {
        return -1;
    }
    struct dlist_item *p_elt = get_pointeur(list, index);
    if (index < list->size / 2)
    {
        for (size_t i = index; i > 0; i--)
        {
            swap_data(&p_elt->data, &p_elt->prev->data);
            p_elt = p_elt->prev;
        }
        int save = list->head->data;
        dlist_pop_front(list);
        return save;
    }
    else
    {
        for (size_t i = index; i < list->size - 1; i++)
        {
            swap_data(&p_elt->data, &p_elt->next->data);
            p_elt = p_elt->next;
        }
        int save = list->tail->data;
        dlist_pop_back(list);
        return save;
    }
}

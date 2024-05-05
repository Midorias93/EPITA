#include "dlist.h"

int dlist_find(const struct dlist *list, int element)
{
    struct dlist_item *p_elt = list->head;
    for (size_t i = 0; i < list->size; i++)
    {
        if (p_elt->data == element)
        {
            return i;
        }
        p_elt = p_elt->next;
    }
    return -1;
}

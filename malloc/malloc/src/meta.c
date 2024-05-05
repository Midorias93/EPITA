#include <unistd.h>

#include "alignment.h"
#include "struct.h"

struct meta *init_meta(void *ptr, size_t empty_size)
{
    struct meta *meta = ptr;
    meta->prev = NULL;
    meta->next = NULL;
    meta->empty_size = empty_size;
    meta->size = empty_size;
    meta->block = NULL;
    return meta;
}

void resize_meta(struct meta *meta, size_t new_size)
{
    meta->empty_size = new_size;
}

struct meta *delet_meta(struct meta *meta, struct meta **first_meta)
{
    if (*first_meta == NULL)
    {
        return NULL;
    }
    struct meta *save = meta;
    if (meta->prev != NULL)
    {
        meta->prev->next = meta->next;
    }
    if (meta->prev == NULL && meta->next != NULL)
    {
        meta->next->prev = NULL;
        *first_meta = meta->next;
    }
    if (meta->next != NULL)
    {
        meta->next->prev = meta->prev;
    }
    if (meta->next == NULL && meta->prev != NULL)
    {
        meta->prev->next = NULL;
    }
    if (meta->prev == NULL && meta->next == NULL)
    {
        *first_meta = NULL;
    }
    return save;
}

void link_page(struct meta *meta1, struct meta *meta2)
{
    meta1->next = meta2;
    meta2->prev = meta1;
}

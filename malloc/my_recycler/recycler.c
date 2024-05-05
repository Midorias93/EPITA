#include "recycler.h"

#include <stdlib.h>

struct recycler *recycler_create(size_t block_size, size_t total_size)
{
    if (block_size % sizeof(size_t) != 0 || block_size == 0 || total_size == 0
        || total_size % block_size != 0)
    {
        return NULL;
    }
    struct recycler *recycler = malloc(sizeof(struct recycler));
    if (recycler == NULL)
    {
        return NULL;
    }
    recycler->block_size = block_size;
    recycler->capacity = total_size / block_size;
    void *free_list = malloc(total_size);
    if (free_list == NULL)
    {
        free(recycler);
        return NULL;
    }
    struct free_list *save = free_list;
    for (int i = 0; i < recycler->capacity; i++)
    {
        save->next = save + block_size;
        save = save->next;
    }
    save->next = NULL;
    recycler->chunk = free_list;
    recycler->free = free_list;
    return recycler;
}

void recycler_destroy(struct recycler *r)
{
    if (r != NULL)
    {
        if (r->free != NULL)
        {
            free(r->free);
        }
        free(r);
    }
}

void *recycler_allocate(struct recycler *r)
{
    if (r == NULL)
    {
        return NULL;
    }
    if (r->free != NULL)
    {
        struct free_list *free_list = r->free;
        r->free = free_list->next;
        return free_list;
    }
    return NULL;
}

void recycler_free(struct recycler *r, void *block)
{
    if (r == NULL || block == NULL)
    {
        return;
    }
    struct free_list *block_free = block;
    block_free->next = r->free;
    r->free = block_free;
}

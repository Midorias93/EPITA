#include <stdlib.h>

#include "heap.h"

struct heap *create_heap(void)
{
    struct heap *new_heap = malloc(sizeof(struct heap));
    if (new_heap == NULL)
    {
        return NULL;
    }
    new_heap->size = 0;
    new_heap->capacity = 8;
    int *list = calloc(8, sizeof(int));
    if (list == NULL)
    {
        return NULL;
    }
    new_heap->array = list;
    return new_heap;
}

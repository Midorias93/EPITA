#include <stddef.h>
#include <stdlib.h>

#include "heap.h"

static struct heap *heap_resize(struct heap *heap)
{
    int *list = calloc(heap->size * 2, sizeof(int));
    if (list == NULL)
    {
        return NULL;
    }
    for (size_t i = 0; i < heap->size; i++)
    {
        list[i] = heap->array[i];
    }
    heap->capacity = heap->size * 2;
    free(heap->array);
    heap->array = list;
    return heap;
}

static void swap(int *a, int *b)
{
    int save = *a;
    *a = *b;
    *b = save;
}

void add(struct heap *heap, int val)
{
    if (heap->size == heap->capacity)
    {
        heap = heap_resize(heap);
    }
    heap->array[heap->size] = val;
    size_t index_val = heap->size++;
    size_t index_papa = heap->size;
    while (index_val != 0
           && heap->array[index_val]
               > heap->array[index_papa = index_val % 2 == 0 ? index_val / 2 - 1
                                                             : index_val / 2])
    {
        swap(&heap->array[index_val], &heap->array[index_papa]);
        index_val = index_papa;
    }
}

#include <stddef.h>
#include <stdio.h>

#include "heap.h"

void print_heap_aux(const struct heap *heap, size_t i)
{
    if (heap->size == 0)
    {
        printf("\n");
        return;
    }
    if (i > heap->size - 1)
    {
        return;
    }
    if (i != 0)
    {
        printf(" %d", heap->array[i]);
    }
    print_heap_aux(heap, i * 2 + 1);
    print_heap_aux(heap, i * 2 + 2);
}

void print_heap(const struct heap *heap)
{
    printf("%d", heap->array[0]);
    print_heap_aux(heap, 0);
    printf("\n");
}

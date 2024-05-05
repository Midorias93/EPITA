#include <assert.h>

#include "heap.h"

static void swap(int *a, int *b)
{
    int save = *a;
    *a = *b;
    *b = save;
}

int pop(struct heap *heap)
{
    assert(heap->size != 0);
    int save = heap->array[0];
    swap(&heap->array[heap->size - 1], &heap->array[0]);
    heap->size--;
    size_t left = 1;
    size_t right = 2;
    for (size_t i = 0; i < heap->size; i++)
    {
        if (left < heap->size && right < heap->size)
        {
            if (heap->array[i] < heap->array[left])
            {
                swap(&heap->array[i], &heap->array[left]);
            }
            if (heap->array[i] < heap->array[right])
            {
                swap(&heap->array[i], &heap->array[right]);
            }
            left = i * 2 + 1;
            right = i * 2 + 2;
        }
    }
    if (heap->size < heap->capacity / 2)
    {
        heap->capacity = heap->capacity / 2 < 8 ? 8 : heap->capacity / 2;
    }
    return save;
}

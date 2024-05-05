#include "heap_sort.h"

#include <stddef.h>

void swap(int *a, int *b)
{
    int save = *a;
    *a = *b;
    *b = save;
}

void heapify_aux(int *array, size_t size, size_t i)
{
    size_t max = i;
    size_t left = 2 * i + 1;
    size_t right = 2 * i + 2;
    if (left < size && array[left] > array[max])
    {
        max = left;
    }
    if (right < size && array[right] > array[max])
    {
        max = right;
    }
    if (max != i)
    {
        swap(&array[i], &array[max]);
        heapify_aux(array, size, max);
    }
}

void heapify(int *array, size_t size)
{
    if (size == 0)
    {
        return;
    }
    for (size_t i = size / 2; i > 0; i--)
    {
        heapify_aux(array, size, i - 1);
    }
}

void heap_sort(int *array, size_t size)
{
    if (size == 0)
    {
        return;
    }
    heapify(array, size);
    for (size_t i = size; i > 0; i--)
    {
        swap(&array[0], &array[i - 1]);
        heapify_aux(array, i - 1, 0);
    }
}

#include <stdio.h>
#include <stdlib.h>

void *my_calloc(size_t n, size_t size)
{
    char *array = malloc(size * n);
    for (size_t i = 0; i < n * size; i++)
    {
        array[i] = 0;
    }
    return array;
}

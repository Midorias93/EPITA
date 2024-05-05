#include "malloc.h"

#include <stddef.h>

__attribute__((visibility("default"))) void *malloc(size_t size)
{
    return my_malloc(size);
}

__attribute__((visibility("default"))) void free(void *ptr)
{
    if (ptr == NULL)
    {
        return;
    }
    my_free(ptr);
}

__attribute__((visibility("default"))) void *realloc(void *ptr, size_t size)
{
    if (size == 0 && ptr != NULL)
    {
        free(ptr);
        return NULL;
    }
    else if (ptr == NULL && size != 0)
    {
        return malloc(size);
    }
    else if (ptr == NULL && size == 0)
    {
        return NULL;
    }
    else
    {
        return my_realloc(ptr, size);
    }
}

__attribute__((visibility("default"))) void *calloc(size_t mmemb, size_t size)
{
    char *array = malloc(size * mmemb);
    for (size_t i = 0; i < mmemb * size; i++)
    {
        array[i] = 0;
    }
    return array;
}

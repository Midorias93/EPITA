#include "alignment.h"

#include <stddef.h>

size_t align(size_t size)
{
    size_t ajout = size % sizeof(long double);
    if (ajout == 0)
    {
        return size;
    }
    for (size_t i = ajout; i < sizeof(long double); i++)
    {
        if (__builtin_add_overflow(size, 1, &size))
        {
            return 0;
        }
    }
    return size;
}

void *deplace_ptr(void *ptr, int deplacement)
{
    char *mooved = ptr;
    mooved = mooved + deplacement;
    return mooved;
}

void *page_begin(void *ptr, size_t page_size)
{
    char *char_ptr = ptr;
    char_ptr = char_ptr - ((size_t)ptr & (page_size - 1));
    return char_ptr;
}

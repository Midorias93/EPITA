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

#include "beware_overflow.h"

#include <stddef.h>

void *beware_overflow(void *ptr, size_t nmemb, size_t size)
{
    char *copy = ptr;
    size_t res;
    if (__builtin_mul_overflow(nmemb, size, &res))
    {
        return NULL;
    }
    else
    {
        return copy + res;
    }
}

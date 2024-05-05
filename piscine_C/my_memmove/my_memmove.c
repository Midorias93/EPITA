#include "my_memmove.h"

#include <stddef.h>

void *my_memmove(void *dest, const void *src, size_t n)
{
    char *copy_dest = dest;
    const char *copy_src = src;
    if (copy_src < copy_dest)
    {
        for (size_t i = n; i > 0; i--)
        {
            *(copy_dest + i - 1) = *(copy_src + i - 1);
        }
    }
    else
    {
        for (size_t i = 0; i < n; i++)
        {
            *copy_dest++ = *copy_src++;
        }
    }
    return dest;
}

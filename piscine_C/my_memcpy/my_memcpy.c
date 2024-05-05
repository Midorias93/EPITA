#include "my_memcpy.h"

#include <stddef.h>

void *my_memcpy(void *dest, const void *source, size_t num)
{
    char *my_dest = dest;
    const char *my_source = source;
    for (size_t i = 0; i < num; i++)
    {
        *my_dest++ = *my_source++;
    }
    return dest;
}

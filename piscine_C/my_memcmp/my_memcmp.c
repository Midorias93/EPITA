#include "my_memcmp.h"

#include <stddef.h>

int my_memcmp(const void *s1, const void *s2, size_t num)
{
    const char *my_s1 = s1;
    const char *my_s2 = s2;
    for (size_t i = 0; i < num; i++)
    {
        if (*my_s1 != *my_s2)
        {
            return *my_s1 - *my_s2;
        }
        my_s1++;
        my_s2++;
    }
    return 0;
}

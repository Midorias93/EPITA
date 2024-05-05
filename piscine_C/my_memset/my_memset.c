#include "my_memset.h"

void *my_memset(void *s, int c, size_t n)
{
    char *my_s = s;
    for (size_t i = 0; i < n; i++)
    {
        my_s[i] = c;
    }
    return my_s;
}

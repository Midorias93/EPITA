#include <stdio.h>

size_t element_count(int *begin, int *end)
{
    if (begin == NULL || end == NULL)
    {
        return 0;
    }
    return end - begin;
}

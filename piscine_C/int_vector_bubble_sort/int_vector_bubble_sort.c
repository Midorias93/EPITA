#include "int_vector_bubble_sort.h"

#include <stddef.h>

static struct int_vector swap(struct int_vector vec, size_t i, size_t j)
{
    int retenu = 0;
    retenu = vec.data[i];
    vec.data[i] = vec.data[j];
    vec.data[j] = retenu;
    return vec;
}

struct int_vector int_vector_bubble_sort(struct int_vector vec)
{
    if (vec.size == 0)
    {
        return vec;
    }
    for (size_t i = vec.size - 1; i >= 1; i--)
    {
        for (size_t j = 0; j < i; j++)
        {
            if (vec.data[j + 1] < vec.data[j])
            {
                vec = swap(vec, j + 1, j);
            }
        }
    }
    return vec;
}

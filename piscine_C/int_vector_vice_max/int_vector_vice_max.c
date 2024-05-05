#include "int_vector_vice_max.h"

#include <stdio.h>

int max_array(const struct int_vector vec)
{
    int max = vec.data[0];
    for (size_t i = 0; i < vec.size; i++)
    {
        if (vec.data[i] > max)
        {
            max = vec.data[i];
        }
    }
    return max;
}
int int_vector_vice_max(const struct int_vector vec)
{
    int max = max_array(vec);
    int vice_max = vec.data[0];
    if (vice_max == max)
    {
        vice_max = vec.data[1];
    }
    for (size_t i = 0; i < vec.size; i++)
    {
        if (vec.data[i] > vice_max && vec.data[i] != max)
        {
            vice_max = vec.data[i];
        }
    }
    return vice_max;
}

#include "int_vector_print.h"

#include <stdio.h>

void int_vector_print(const struct int_vector vec)
{
    for (size_t i = 0; i < vec.size - 1; i++)
    {
        printf("%d ", vec.data[i]);
    }
    printf("%d\n", vec.data[vec.size - 1]);
}

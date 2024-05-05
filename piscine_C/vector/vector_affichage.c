#include <stddef.h>
#include <stdio.h>

#include "vector.h"

void vector_print(const struct vector *v)
{
    if (v == NULL || v->size == 0)
    {
        printf("\n");
    }
    else
    {
        for (size_t i = 0; i < v->size - 1; i++)
        {
            printf("%d,", v->data[i]);
        }
        printf("%d\n", v->data[v->size - 1]);
    }
}

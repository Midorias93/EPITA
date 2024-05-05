#include "int_vector_hill.h"

#include <stdio.h>

int int_vector_hill(struct int_vector vec)
{
    if (vec.size == 0)
    {
        return -1;
    }
    for (size_t i = 0; i < vec.size; i++)
    {
        if (vec.data[i] < 0)
        {
            return -1;
        }
    }
    size_t indice = 0;
    size_t indice_top = 0;
    while (indice < vec.size - 1 && vec.data[indice] <= vec.data[indice + 1])
    {
        if (vec.data[indice + 1] > vec.data[indice])
        {
            indice_top = indice + 1;
        }
        indice++;
    }
    if (indice == vec.size - 1)
    {
        return indice;
    }
    else
    {
        for (size_t i = indice; i < vec.size - 1; i++)
        {
            if (vec.data[i] < vec.data[i + 1])
            {
                return -1;
            }
        }
        return indice_top;
    }
}

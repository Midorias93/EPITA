#include "int_vector_insert_sort.h"

#include <stddef.h>

static unsigned array_min(const int arr[], unsigned start, unsigned size)
{
    int indice_min = start;
    for (size_t i = start; i < size; i++)
    {
        if (arr[i] < arr[indice_min])
        {
            indice_min = i;
        }
    }
    return indice_min;
}

static struct int_vector swap(struct int_vector vec, size_t i, size_t j)
{
    int retenu = 0;
    retenu = vec.data[i];
    vec.data[i] = vec.data[j];
    vec.data[j] = retenu;
    return vec;
}

struct int_vector int_vector_insert_sort(struct int_vector vec)
{
    size_t indice_min = 0;
    for (size_t i = 0; i < vec.size; i++)
    {
        indice_min = array_min(vec.data, i, vec.size);
        vec = swap(vec, indice_min, i);
    }
    return vec;
}

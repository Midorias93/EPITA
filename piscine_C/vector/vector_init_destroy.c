#include <stdlib.h>

#include "vector.h"

struct vector *vector_init(size_t n)
{
    struct vector *new_vector = malloc(sizeof(struct vector));
    if (new_vector == NULL)
    {
        return NULL;
    }
    new_vector->size = 0;
    new_vector->capacity = n;
    int *list = calloc(n, sizeof(int));
    if (list == NULL)
    {
        return NULL;
    }
    new_vector->data = list;
    return new_vector;
}

void vector_destroy(struct vector *v)
{
    if (v == NULL)
    {
        return;
    }
    free(v->data);
    free(v);
}

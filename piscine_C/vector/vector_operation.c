#include <stdlib.h>

#include "vector.h"

struct vector *vector_resize(struct vector *v, size_t n)
{
    if (v == NULL)
    {
        return NULL;
    }
    if (v->capacity == n)
    {
        return v;
    }
    else
    {
        int *list = calloc(n, sizeof(int));
        size_t arret = v->size < n ? v->size : n;
        for (size_t i = 0; i < arret; i++)
        {
            list[i] = v->data[i];
        }
        v->capacity = n;
        v->size = v->size > n ? n : v->size;
        free(v->data);
        v->data = list;
    }
    return v;
}

struct vector *vector_append(struct vector *v, int elt)
{
    if (v == NULL)
    {
        return NULL;
    }
    if (v->size == v->capacity)
    {
        v = vector_resize(v, v->size * 2);
        v->size++;
        v->data[v->size - 1] = elt;
    }
    else
    {
        v->data[v->size] = elt;
        v->size++;
    }
    return v;
}

struct vector *vector_reset(struct vector *v, size_t n)
{
    if (v == NULL)
    {
        return NULL;
    }
    struct vector *retenu = v;
    struct vector *reset = vector_init(n);
    v = reset;
    vector_destroy(retenu);
    return v;
}

static void swap(int *a, int *b)
{
    int save = *a;
    *a = *b;
    *b = save;
}

struct vector *vector_insert(struct vector *v, size_t i, int elt)
{
    if (v == NULL || i > v->size)
    {
        return NULL;
    }
    else
    {
        v = vector_append(v, elt);
        for (size_t j = v->size - 1; j > i; j--)
        {
            swap(&v->data[j], &v->data[j - 1]);
        }
    }
    return v;
}

struct vector *vector_remove(struct vector *v, size_t i)
{
    if (v == NULL || i >= v->size)
    {
        return NULL;
    }
    else
    {
        for (size_t j = i; j < v->size - 1; j++)
        {
            swap(&v->data[j], &v->data[j + 1]);
        }
        v->size = v->size - 1;
    }
    if (v->size < v->capacity / 2)
    {
        v->capacity = v->capacity / 2;
    }
    return v;
}

#include <stddef.h>

typedef int (*f_cmp)(const void *, const void *);

int min_indice(void **array, int start, f_cmp comp)
{
    int indice_min = start;
    for (size_t i = start; array[i] != NULL; i++)
    {
        if (comp(array[i], array[indice_min]) < 0)
        {
            indice_min = i;
        }
    }
    return indice_min;
}

static void **swap(void **array, int i, int j)
{
    void *retenu = array[i];
    array[i] = array[j];
    array[j] = retenu;
    return array;
}

void insertion_sort(void **array, f_cmp comp)
{
    int indice_min = 0;
    for (int i = 0; array[i] != NULL; i++)
    {
        indice_min = min_indice(array, i, comp);
        array = swap(array, indice_min, i);
    }
}

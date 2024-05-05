#include <stdio.h>

unsigned array_min(const int arr[], unsigned start, unsigned size)
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

void selection_sort(int arr[], unsigned size)
{
    int retenu = 0;
    int indice_min = 0;
    for (size_t i = 0; i < size; i++)
    {
        indice_min = array_min(arr, i, size);
        {
            retenu = arr[indice_min];
            arr[indice_min] = arr[i];
            arr[i] = retenu;
        }
    }
}

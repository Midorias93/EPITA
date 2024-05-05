#include <stdio.h>

void bubble_sort(int array[], size_t size)
{
    if (size == 0)
    {
        return;
    }
    int retenu = 0;
    for (size_t i = size - 1; i >= 1; i--)
    {
        for (size_t j = 0; j < i; j++)
        {
            if (array[j + 1] < array[j])
            {
                retenu = array[j + 1];
                array[j + 1] = array[j];
                array[j] = retenu;
            }
        }
    }
}

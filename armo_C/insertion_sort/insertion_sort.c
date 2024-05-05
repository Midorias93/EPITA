#include <stddef.h>

void insertion_sort(int array[], size_t size)
{
    int retenu = 0;
    for (size_t i = 1; i < size; i++)
    {
        for (size_t j = i; j > 0; j--)
        {
            if (array[j] < array[j - 1])
            {
                retenu = array[j - 1];
                array[j - 1] = array[j];
                array[j] = retenu;
            }
        }
    }
}

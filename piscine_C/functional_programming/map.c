#include "functional_programming.h"

void map(int *array, size_t len, void (*func)(int *))
{
    for (size_t i = 0; i < len; i++)
    {
        func(&array[i]);
    }
}

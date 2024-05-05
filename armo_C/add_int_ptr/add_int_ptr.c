#include <stdio.h>

int *add_int_ptr(int *a, int *b)
{
    if (a == NULL || b == NULL)
    {
        return a;
    }
    else
    {
        *a = *a + *b;
        return a;
    }
}

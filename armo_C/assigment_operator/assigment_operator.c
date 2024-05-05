#include <stddef.h>

void plus_equal(int *a, int *b)
{
    *a = *a + *b;
}

void minus_equal(int *a, int *b)
{
    *a = *a - *b;
}

void mult_equal(int *a, int *b)
{
    *a = *a * *b;
}

int div_equal(int *a, int *b)
{
    int rest = 0;
    if (*b == 0)
    {
        return 0;
    }
    else
    {
        rest = *a % *b;
        *a = *a / *b;
        return rest;
    }
}

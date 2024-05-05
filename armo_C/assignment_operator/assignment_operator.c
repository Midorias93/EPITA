#include <stddef.h>

void plus_equal(int *a, int *b)
{
    if (a == NULL || b == NULL || (a == NULL && b == NULL))
    {
        return;
    }
    *a = *a + *b;
}

void minus_equal(int *a, int *b)
{
    if (a == NULL || b == NULL || (a == NULL && b == NULL))
    {
        return;
    }
    *a = *a - *b;
}

void mult_equal(int *a, int *b)
{
    if (a == NULL || b == NULL || (a == NULL && b == NULL))
    {
        return;
    }
    *a = *a * *b;
}

int div_equal(int *a, int *b)
{
    int rest = 0;
    if (a == NULL || b == NULL || (a == NULL && b == NULL))
    {
        return 0;
    }
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

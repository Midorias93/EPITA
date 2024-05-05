#include <stdio.h>

int int_sqrt(int n)
{
    if (n < 0)
    {
        return -1;
    }
    if (n == 0)
    {
        return 0;
    }
    if (n == 1)
    {
        return 1;
    }
    int x = 1;
    while ((x * x) < n)
    {
        x++;
    }
    if ((x + 1 - n) < (x - n) && x * x != n)
    {
        return x + 1;
    }
    if ((x - 1 - n) < (x - n) && x * x != n)
    {
        return x - 1;
    }
    return x;
}

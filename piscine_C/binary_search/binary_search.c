#include <stdio.h>

int binary_search(const int vec[], int size, int elt)
{
    size_t a = 0;
    size_t b = size;
    size_t c = 0;
    while (a < b)
    {
        c = ((b - a) / 2) + a;
        if (vec[c] == elt)
        {
            return c;
        }
        else if (elt > vec[c])
        {
            a = c + 1;
        }
        else
        {
            b = c;
        }
    }
    return -1;
}

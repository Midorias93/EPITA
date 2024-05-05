#include <stddef.h>

void pointer_swap(int **a, int **b)
{
    int *c = *a;
    *a = *b;
    *b = c;
}

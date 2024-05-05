#include <stdio.h>
#include <stdlib.h>

void sieve(int n)
{
    if (n <= 2)
    {
        return;
    }
    int compte = 0;
    int *list = calloc(sizeof(int), n);
    for (int i = 2; i < n; i++)
    {
        if (list[i] == 0)
        {
            list[i] = 1;
            for (int j = 2 * i; j < n; j = j + i)
            {
                list[j] = 2;
            }
        }
    }
    for (int i = 2; i < n; i++)
    {
        if (list[i] == 1)
        {
            compte++;
        }
    }
    printf("%d\n", compte);
    free(list);
}

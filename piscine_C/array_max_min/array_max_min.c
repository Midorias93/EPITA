#include <stdio.h>

void array_max_min(int tab[], size_t len, int *max, int *min)
{
    if (len == 0 || tab == NULL)
    {
        return;
    }
    *max = tab[0];
    *min = tab[0];
    for (size_t i = 0; i < len; i++)
    {
        if (*max < tab[i])
        {
            *max = tab[i];
        }
        if (*min > tab[i])
        {
            *min = tab[i];
        }
    }
}

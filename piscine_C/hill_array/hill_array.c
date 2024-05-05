#include "hill_array.h"

#include <stdio.h>

int top_of_the_hill(int tab[], size_t len)
{
    if (tab == NULL || len == 0)
    {
        return -1;
    }
    for (size_t i = 0; i < len; i++)
    {
        if (tab[i] < 0)
        {
            return -1;
        }
    }
    size_t indice = 0;
    size_t indice_top = 0;
    while (indice < len - 1 && tab[indice] <= tab[indice + 1])
    {
        if (tab[indice + 1] > tab[indice])
        {
            indice_top = indice + 1;
        }
        indice++;
    }
    if (indice == len - 1)
    {
        return indice;
    }
    else
    {
        for (size_t i = indice; i < len - 1; i++)
        {
            if (tab[i] < tab[i + 1])
            {
                return -1;
            }
        }
        return indice_top;
    }
}

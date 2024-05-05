#include "functional_programming.h"

int foldl(int *array, size_t len, int (*func)(int, int))
{
    int resultat = func(0, array[0]);
    for (size_t i = 1; i < len; i++)
    {
        resultat = func(resultat, array[i]);
    }
    return resultat;
}

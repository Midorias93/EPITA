#include "functional_programming.h"

int foldr(int *array, size_t len, int (*func)(int, int))
{
    int resultat = func(array[len - 1], 0);
    for (size_t i = len - 1; i > 0; i--)
    {
        resultat = func(array[i - 1], resultat);
    }
    return resultat;
}

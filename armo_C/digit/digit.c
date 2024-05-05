#include <stdio.h>

int puissance(int x, int n)
{
    int compte = 1;
    for (int i = 0; i < n; i++)
    {
        compte = compte * x;
    }
    return compte;
}

unsigned int digit(int n, int k)
{
    int resultat = 0;
    if (n < 0)
    {
        return resultat;
    }
    else if (k < 0)
    {
        return resultat;
    }
    else
    {
        return ((n % puissance(10, k) - n % puissance(10, k - 1))
                / puissance(10, k - 1));
    }
}

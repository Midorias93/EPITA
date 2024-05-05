#include <stdio.h>

unsigned int puissance_10(unsigned int n)
{
    int compte = 1;
    for (unsigned int i = 0; i <= n; i++)
    {
        compte = compte * 10;
    }
    return compte;
}

unsigned int aux(unsigned int n, unsigned int nb_D)
{
    if (n % puissance_10(nb_D) == 0)
    {
        return nb_D;
    }
    else
    {
        return aux(n / 10, nb_D + 1);
    }
}

unsigned int number_digits_rec(unsigned int n)
{
    if (n == 0)
    {
        return 1;
    }
    return aux(n, 0);
}

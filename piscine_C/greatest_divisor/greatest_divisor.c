#include <stdio.h>

unsigned int greatest_divisor(unsigned int n)
{
    unsigned int resultat = 1;
    unsigned int i = 1;
    while (i <= n / 2)
    {
        if (n % i == 0)
        {
            resultat = i;
        }
        i++;
    }
    return resultat;
}

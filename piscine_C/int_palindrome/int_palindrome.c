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

int revers(int n)
{
    int nombre_revers = 0;
    int retenu = n;
    while (retenu > 10)
    {
        nombre_revers = nombre_revers * 10 + retenu % 10;
        retenu = retenu / 10;
    }
    nombre_revers = nombre_revers * 10 + retenu;
    return nombre_revers;
}

int int_palindrome(int n)
{
    if (n < 0)
    {
        return 0;
    }
    if (n == revers(n))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

#include <stdio.h>

int P_10(int n)
{
    if (n == 0)
    {
        return 1;
    }
    int p = 10;
    for (int i = 1; i < n; i++)
    {
        p = 10 * p;
    }
    return p;
}

int test_alpha(char c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int my_atoi(const char *str)
{
    int taille = 0;
    int bit_de_signe = 0;
    while (str[taille] != '\0')
    {
        if (test_alpha(str[taille]))
        {
            return 0;
        }
        taille++;
    }
    taille--;
    int i = 0;
    int resultat = 0;
    while (str[i] == ' ')
    {
        i++;
    }
    if (str[i] == '-')
    {
        bit_de_signe = 1;
        i++;
    }
    if (str[i] == '+')
    {
        bit_de_signe = 0;
        i++;
    }
    while (i <= taille && (str[i] != '-' && str[i] != '+' && str[i] != ' '))
    {
        resultat = resultat + P_10(taille - i) * (str[i] - '0');
        i++;
    }
    if (i < taille)
    {
        return 0;
    }
    if (bit_de_signe == 1)
    {
        return -resultat;
    }
    return resultat;
}

#include <stdio.h>

int my_pow(int a, int b)
{
    if (b == 0)
    {
        return 1;
    }
    if (b % 2 == 0)
    {
        return my_pow(a, b / 2) * my_pow(a, b / 2);
    }
    else
    {
        return a * my_pow(a, b / 2) * my_pow(a, b / 2);
    }
}

int check(const char *str, const char *alphabet, int t_str, int t_base)
{
    int val = 0;
    for (int i = 0; i < t_str; i++)
    {
        val = 0;
        for (int j = 0; j < t_base; j++)
        {
            if (str[i] == alphabet[j])
            {
                val = 1;
                break;
            }
        }
        if (val == 0)
        {
            return 1;
        }
    }
    return 0;
}

int my_atoi_base(const char *str, const char *base)
{
    int val = 0;
    while (*str == ' ')
    {
        str++;
    }
    if (str[0] == '+' || str[0] == '-')
    {
        if (str[0] == '-')
        {
            val = 1;
        }
        str++;
    }
    int taille_str = 0;
    int taille_base = 0;
    while (str[taille_str] != '\0')
    {
        taille_str++;
    }
    while (base[taille_base] != '\0')
    {
        taille_base++;
    }
    if (check(str, base, taille_str, taille_base))
    {
        return 0;
    }
    int resultat = 0;
    int j = 0;
    for (int i = taille_str - 1; i >= 0; i--)
    {
        j = 0;
        while (j < taille_base && str[i] != base[j])
        {
            j++;
        }
        resultat = resultat + j * my_pow(taille_base, taille_str - i - 1);
    }
    if (val == 1)
    {
        return -resultat;
    }
    return resultat;
}

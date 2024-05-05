#include <stdio.h>

int my_strcmp(const char *s1, const char *s2)
{
    int taille1 = 0;
    int taille2 = 0;
    while (s1[taille1] != '\0')
    {
        taille1++;
    }
    while (s2[taille2] != '\0')
    {
        taille2++;
    }
    int i = 0;
    while (i < taille1 && i < taille2)
    {
        if (s1[i] < s2[i])
        {
            return -1;
        }
        if (s1[i] > s2[i])
        {
            return 1;
        }
        i++;
    }
    if (taille1 < taille2)
    {
        return -1;
    }
    else if (taille1 > taille2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

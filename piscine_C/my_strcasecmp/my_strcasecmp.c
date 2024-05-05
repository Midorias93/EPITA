#include "my_strcasecmp.h"

#include <stdio.h>

int my_strcasecmp(const char *s1, const char *s2)
{
    int taille1 = 0;
    int taille2 = 0;
    char car1;
    char car2;
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
        car1 = s1[i];
        car2 = s2[i];
        if (car1 >= 'A' && car1 <= 'Z')
        {
            car1 += 32;
        }
        if (car2 >= 'A' && car2 <= 'Z')
        {
            car2 += 32;
        }
        if (car1 < car2)
        {
            return -1;
        }
        if (car1 > car2)
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

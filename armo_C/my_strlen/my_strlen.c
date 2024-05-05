#include <stdio.h>

size_t my_strlen(const char *s)
{
    size_t taille = 0;
    while (s[taille] != 0)
    {
        taille++;
    }
    return taille;
}

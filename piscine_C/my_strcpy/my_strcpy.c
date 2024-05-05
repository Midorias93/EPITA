#include <stdio.h>

char *my_strcpy(char *dest, const char *source)
{
    int taille = 0;
    while (source[taille] != '\0')
    {
        dest[taille] = source[taille];
        taille++;
    }
    dest[taille] = '\0';
    return dest;
}

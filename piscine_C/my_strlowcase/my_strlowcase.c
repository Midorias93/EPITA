#include "my_strlowcase.h"

#include <stddef.h>

void my_strlowcase(char *str)
{
    size_t taille = 0;
    while (str[taille] != '\0')
    {
        taille++;
    }
    for (size_t i = 0; i < taille; i++)
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
        {
            str[i] = str[i] + 32;
        }
    }
}

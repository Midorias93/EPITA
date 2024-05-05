#include "my_strlen.h"

#include <stdio.h>

size_t my_strlen(const char *s)
{
    size_t compte = 0;
    while (s[compte] != '\0')
    {
        compte++;
    }
    return compte;
}

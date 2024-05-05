#include "my_strspn.h"

#include <stddef.h>
#include <stdio.h>

size_t my_strspn(const char *s, const char *accept)
{
    int val = 1;
    const char *first = accept;
    size_t compte = 0;
    while (*s != '\0')
    {
        accept = first;
        val = 0;
        while (*accept != '\0')
        {
            if (*s != *accept)
            {
                val = 0;
            }
            else
            {
                val = 1;
                break;
            }
            accept++;
        }
        if (val == 1)
        {
            compte++;
        }
        else
        {
            return compte;
        }
        s++;
    }
    return compte;
}

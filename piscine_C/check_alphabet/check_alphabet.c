#include "check_alphabet.h"

#include <stdio.h>

int check_alphabet(const char *str, const char *alphabet)
{
    if (alphabet == NULL || *alphabet == '\0')
    {
        return 1;
    }
    int i = 0;
    int j = 0;
    while (alphabet[i] != '\0')
    {
        j = 0;
        while (str[j] != '\0')
        {
            if (str[j] == alphabet[i])
            {
                break;
            }
            j++;
        }
        i++;
        if (str[j] != '\0')
        {
            continue;
        }
        return 0;
    }
    return 1;
}

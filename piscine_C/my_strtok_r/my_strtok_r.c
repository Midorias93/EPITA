#include <stdio.h>

int is_delim(char c, const char *delim)
{
    for (int i = 0; delim[i] != '\0'; i++)
    {
        if (c == delim[i])
        {
            return 1;
        }
    }
    return 0;
}

char *my_strtok_r(char *str, const char *delim, char **saveptr)
{
    if (str == NULL && *saveptr == NULL)
    {
        return NULL;
    }
    else
    {
        *saveptr = str != NULL ? str : *saveptr;
        while (**saveptr != '\0' && is_delim(**saveptr, delim))
        {
            *saveptr = *saveptr + 1;
        }
        if (**saveptr == '\0')
        {
            return NULL;
        }
        char *save = *saveptr;
        while (**saveptr != '\0' && !is_delim(**saveptr, delim))
        {
            *saveptr = *saveptr + 1;
        }
        if (**saveptr == '\0')
        {
            return save;
        }
        else
        {
            **saveptr = '\0';
            *saveptr = *saveptr + 1;
            return save;
        }
    }
}

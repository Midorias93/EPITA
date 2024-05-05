#include "count_integers.h"

#include <stddef.h>
#include <stdio.h>

int count_integers(const char *file_in)
{
    FILE *file = fopen(file_in, "r");
    if (file == NULL)
    {
        return -1;
    }
    char car = fgetc(file);
    int nb_int = 0;
    while (car != EOF)
    {
        if (car <= '9' && car >= '0')
        {
            while (car != EOF && car <= '9' && car >= '0')
            {
                car = fgetc(file);
            }
            nb_int++;
        }
        else
        {
            car = fgetc(file);
        }
    }
    fclose(file);
    return nb_int;
}

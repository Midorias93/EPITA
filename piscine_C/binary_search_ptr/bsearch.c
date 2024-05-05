#include "bsearch.h"

#include <stdio.h>

int *binary_search(int *begin, int *end, int elt)
{
    int taille = end - begin;
    int *cp_begin = begin;
    if (begin == end)
    {
        return begin;
    }
    int *milieu = NULL;
    while (begin < end)
    {
        milieu = ((end - begin) / 2) + begin;
        if (*milieu == elt)
        {
            return milieu;
        }
        else if (elt > *milieu)
        {
            begin = milieu + 1;
        }
        else
        {
            end = milieu;
        }
    }
    int i = 0;
    while (i < taille && *cp_begin < elt)
    {
        i++;
        cp_begin++;
    }
    return cp_begin;
}

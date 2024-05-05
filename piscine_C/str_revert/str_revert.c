#include "str_revert.h"

void str_revert(char str[])
{
    int taille = 0;
    char retenu;
    int indice = 0;
    while (str[taille] != '\0')
    {
        taille++;
    }
    taille--;
    while (taille > indice)
    {
        retenu = str[taille];
        str[taille] = str[indice];
        str[indice] = retenu;
        taille--;
        indice++;
    }
}

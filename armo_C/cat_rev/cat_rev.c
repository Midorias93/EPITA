#include <stdio.h>

int main(int nb_path, char *path[])
{
    if (nb_path != 2)
    {
        return 1;
    }
    FILE *file = fopen(path[1], "r");

    if (file == NULL)
    {
        return 2;
    }
    int ligne[512];
    ligne[0] = fgetc(file);
    int car = ligne[0];
    int taille = 1;
    while (car != EOF)
    {
        while (car != EOF && car != '\n')
        {
            ligne[taille] = fgetc(file);
            car = ligne[taille];
            taille++;
        }
        taille--;
        while (taille != 0)
        {
            taille--;
            putchar(ligne[taille]);
        }
        ligne[0] = fgetc(file);
        car = ligne[0];
        taille++;
        putchar('\n');
    }
    fclose(file);
    return 0;
}

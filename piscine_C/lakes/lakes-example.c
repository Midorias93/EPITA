/* lakes-example.c */
#include <stdio.h>
#include <stdlib.h>

#include "lakes.h"

static inline void free_all(char **map, int index)
{
    for (int i = 0; i < index; i++)
        free(map[i]);

    free(map);
}

int main(int argc, char **argv)
{
    char **map;
    FILE *f;
    int x;
    int y;

    if (argc != 2)
        return 1;

    f = fopen(argv[1], "r");
    fscanf(f, "%d %d\n", &x, &y);
    map = malloc(sizeof(char *) * y);
    if (!map)
        return 1;

    for (int i = 0; i < y; i++)
    {
        map[i] = malloc(sizeof(char) * x);
        if (!map[i])
        {
            free_all(map, i);
            return 1;
        }
        for (int j = 0; j < x; j++)
            map[i][j] = fgetc(f);
        fgetc(f);
    }
    printf("%d\n", lakes(map, x, y));
    free_all(map, y);
    fclose(f);
    return 0;
}

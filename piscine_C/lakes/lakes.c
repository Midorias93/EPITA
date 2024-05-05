#include "lakes.h"

void transforme(char **map, int co1, int co2)
{
    map[co1][co2] = '#';
    if (map[co1 - 1][co2] == '.')
    {
        transforme(map, co1 - 1, co2);
    }
    if (map[co1][co2 - 1] == '.')
    {
        transforme(map, co1, co2 - 1);
    }
    if (map[co1 + 1][co2] == '.')
    {
        transforme(map, co1 + 1, co2);
    }
    if (map[co1][co2 + 1] == '.')
    {
        transforme(map, co1, co2 + 1);
    }
}

int lakes(char **map, int width, int height)
{
    int compte = 0;
    int co[2] = { 0, 0 };
    for (int j = 0; j < width; j++)
    {
        for (int i = 0; i < height; i++)
        {
            co[0] = i;
            co[1] = j;
            if (map[co[0]][co[1]] == '.')
            {
                transforme(map, co[0], co[1]);
                compte++;
            }
        }
    }
    return compte;
}

#include <stdio.h>

void apply_lut(unsigned char mat[4][4], const unsigned char lut[256])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            mat[i][j] = lut[mat[i][j]];
        }
    }
}

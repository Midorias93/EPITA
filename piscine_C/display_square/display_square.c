#include <stdio.h>

void display_square(int width)
{
    if (width == 1)
    {
        putchar('*');
        putchar('\n');
        return;
    }
    if (width <= 0)
    {
        return;
    }
    else
    {
        if (width % 2 == 0)
        {
            width++;
        }
        int rows = ((width + 1) / 2) - 2;
        for (int i = 0; i < width; i++)
        {
            putchar('*');
        }
        putchar('\n');
        for (int i = 0; i < rows; i++)
        {
            putchar('*');
            for (int j = 0; j < (width - 2); j++)
            {
                putchar(' ');
            }
            putchar('*');
            putchar('\n');
        }
        for (int i = 0; i < width; i++)
        {
            putchar('*');
        }
        putchar('\n');
    }
}

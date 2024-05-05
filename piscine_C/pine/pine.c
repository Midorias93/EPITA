#include <stdio.h>

int pine(unsigned n)
{
    if (n < 3)
    {
        return 1;
    }
    else
    {
        unsigned i = 1;
        while (i < (1 + n * 2))
        {
            for (unsigned j = 0; j < ((1 + n * 2) - i) / 2 - 1; j++)
            {
                putchar(' ');
            }
            for (unsigned j = 0; j < i; j++)
            {
                putchar('*');
            }
            putchar('\n');
            i += 2;
        }
        for (unsigned int x = 0; x < (n / 2); x++)
        {
            for (unsigned j = 0; j < (i / 2) - 1; j++)
            {
                putchar(' ');
            }
            putchar('*');
            putchar('\n');
        }
        return 0;
    }
}

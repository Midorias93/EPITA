#include <stdio.h>

int main(int nb_arg, char *arg[])
{
    if (nb_arg != 3)
    {
        return 1;
    }
    for (int i = 0; i < (*arg[2] - 48); i++)
    {
        puts(arg[1]);
    }
    return 0;
}

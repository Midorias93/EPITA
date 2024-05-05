#include "evalexpr.h"

int main (int argc, char *argv[])
{
    if (argc < 2)
    {
        if (argc == 2 && is_rpn(argv[1]) == 1)
        {
            return 4;
        }
        else if (argc == 2 && is_rpn(argv[1]) == 0)
        {
            char buffer[300];
            int error = 0;
            fread(buffer, sizeof(char), 300, stdin);
            struct fifo *expression = pars(buffer);
            printf("%d\n", calcul_rpn(expression, &error));
        }
        else
        {
            char buffer[300];
            int error = 0;
            fread(buffer, sizeof(char), 300, stdin);
            struct fifo *expression = pars(buffer);
            expression = convert_standar(expression, &error);
            printf("%d\n", calcul_rpn(expression, &error));
        }
    }
    else
    {
        return 4;
    }
}


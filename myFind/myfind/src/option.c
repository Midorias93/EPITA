#include "option.h"

#include "my_find.h"
#include "string.h"

int cores_option(char *str)
{
    if (strcmp(str, "-d") == 0)
    {
        return D;
    }
    else if (strcmp(str, "-H") == 0)
    {
        return H;
    }
    else if (strcmp(str, "-L") == 0)
    {
        return L;
    }
    else if (strcmp(str, "-P") == 0)
    {
        return P;
    }
    else
    {
        return -1;
    }
}

void option_search(struct info *info, int argc, char *argv[])
{
    for (int i = 1; i < argc && cores_option(argv[i]) != -1; i++)
    {
        info->option = cores_option(argv[i]);
        info->depart = info->depart + 1;
    }
}

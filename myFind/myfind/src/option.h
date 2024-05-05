#ifndef OPTION_H
#define OPTION_H

#include "info.h"

enum option
{
    D = 0,
    H,
    L,
    P,
};

void option_search(struct info *info, int argc, char *argv[]);

#endif // OPTION_H

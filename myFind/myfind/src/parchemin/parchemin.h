#ifndef PARCHEMIN_H
#define PARCHEMIN_H

#include "../info.h"

struct parchemin
{
    int size;
    char **chemins;
};

struct parchemin *init_parchemin(struct info *info, int argc, char *argv[]);
void destroy_parchemin(struct parchemin *parchemin);

#endif // PARCHEMIN_H

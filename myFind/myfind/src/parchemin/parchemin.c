#include "parchemin.h"

#include <stdlib.h>
#include <string.h>

static int condition(char c)
{
    if (c != '-' && c != '!' && c != '(')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

struct parchemin *init_parchemin(struct info *info, int argc, char *argv[])
{
    struct parchemin *parchemin = malloc(sizeof(struct parchemin));
    int nb_chemin = 0;
    int save = info->depart;
    while (save < argc && condition(*argv[save]))
    {
        nb_chemin++;
        save++;
    }
    if (nb_chemin == 0)
    {
        char **list = malloc(sizeof(char *) * 1);
        char *chemin = malloc(sizeof(char) * 2);
        chemin[0] = '.';
        chemin[1] = '\0';
        list[0] = chemin;
        parchemin->chemins = list;
        parchemin->size = 1;
        return parchemin;
    }
    char **list = malloc(sizeof(char *) * nb_chemin);
    char *chemin = NULL;
    int tp = 0;
    for (int i = 0; i < nb_chemin; i++)
    {
        tp = strlen(argv[info->depart + i]);
        chemin = malloc(sizeof(char) * tp + 1);
        for (int j = 0; j < tp + 1; j++)
        {
            chemin[j] = argv[info->depart + i][j];
        }
        list[i] = chemin;
    }
    info->depart = info->depart + nb_chemin;
    parchemin->chemins = list;
    parchemin->size = nb_chemin;
    return parchemin;
}

void destroy_parchemin(struct parchemin *parchemin)
{
    for (int i = 0; i < parchemin->size; i++)
    {
        free(parchemin->chemins[i]);
    }
    free(parchemin->chemins);
    free(parchemin);
}

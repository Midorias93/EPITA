#include "my_c_tail.h"

#include <stdlib.h>
#include <unistd.h>

static char **swap(char **str, int n)
{
    char **new_save = malloc(sizeof(char *) * n);
    for (int i = n - 1; i > 0; i--)
    {
        new_save[i - 1] = str[i];
    }
    free(str[0]);
    free(str);
    return new_save;
}

static int my_strlen(char *str)
{
    int taille = 0;
    while (str[taille] != '\n')
    {
        taille++;
    }
    return taille;
}

static char *my_get_line(char **buffer, int *a)
{
    int taille = 0;
    char *list = NULL;
    while (a != 0 && **buffer != '\n')
    {
        taille++;
        list = realloc(list, sizeof(char) * taille);
        list[taille - 1] = **buffer;
        *a = read(STDIN_FILENO, *buffer, 1);
    }
    list = realloc(list, sizeof(char) * taille + 1);
    list[taille] = **buffer;
    *a = read(STDIN_FILENO, *buffer, 1);
    return list;
}

void stdintail(unsigned int n)
{
    if (n == 0)
    {
        return;
    }
    unsigned int compte = 0;
    char **save = malloc(sizeof(char *) * n);
    char *buffer = malloc(sizeof(char));
    int a = read(STDIN_FILENO, buffer, 1);
    while (a != 0)
    {
        if (compte < n)
        {
            save[compte] = my_get_line(&buffer, &a);
            compte++;
        }
        else
        {
            save = swap(save, n);
            save[n - 1] = my_get_line(&buffer, &a);
        }
    }
    for (unsigned int j = 0; j < compte; j++)
    {
        write(STDOUT_FILENO, save[j], my_strlen(save[j]) + 1);
        free(save[j]);
    }
    free(save);
    free(buffer);
}

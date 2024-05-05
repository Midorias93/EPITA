#include "null_terminated_arrays.h"

#include <stddef.h>

static int len_matrix(const char ***matrix)
{
    int taille = 0;
    while (matrix[taille] != NULL)
    {
        taille++;
    }
    return taille;
}

static int len_array(const char **array)
{
    int taille = 0;
    while (array[taille] != NULL)
    {
        taille++;
    }
    return taille;
}

static void swap_matrix(const char ***matrix, int i, int j)
{
    const char **save = matrix[i];
    matrix[i] = matrix[j];
    matrix[j] = save;
}

static void swap_array(const char **array, int i, int j)
{
    const char *save = array[i];
    array[i] = array[j];
    array[j] = save;
}

void reverse_matrix(const char ***matrix)
{
    int taille_matrix = len_matrix(matrix);
    int taille_array = 0;
    for (int i = 0; i < taille_matrix; i++)
    {
        taille_array = len_array(matrix[i]);
        for (int j = 0; j < taille_array / 2; j++)
        {
            swap_array(matrix[i], j, taille_array - j - 1);
        }
    }
    for (int i = 0; i < taille_matrix / 2; i++)
    {
        swap_matrix(matrix, i, taille_matrix - i - 1);
    }
}

#include <stddef.h>
#include <stdio.h>

size_t len_str(const char *str)
{
    size_t len = 0;
    while (str[len] != '\0')
    {
        len++;
    }
    return len;
}

size_t indice_max(int *list, size_t size)
{
    size_t indice_max = 0;
    for (size_t i = 0; i < size; i++)
    {
        if (list[i] > list[indice_max])
        {
            indice_max = i;
        }
    }
    return indice_max;
}

void freq_analysis(const char text[], const char table[])
{
    int occurence[26] = { 0 };
    for (int i = 0; text[i] != '\0'; i++)
    {
        occurence[text[i] - 'A']++;
    }
    size_t size_table = len_str(table);
    size_t i_max = 0;
    char affichage[26] = { 0 };
    for (size_t i = 0; i < size_table; i++)
    {
        i_max = indice_max(occurence, 26);
        occurence[i_max] = 0;
        affichage[i_max] = table[i];
    }
    int lettre = 0;
    for (size_t i = 0; i < 26; i++)
    {
        if (affichage[i] != 0)
        {
            lettre = i + 'A';
            printf("%c %c\n", lettre, affichage[i]);
        }
    }
}

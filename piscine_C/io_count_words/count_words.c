#include <stdio.h>

int my_issapce(char c)
{
    switch (c)
    {
    case ' ':
        return 1;
    case '\t':
        return 1;
    case '\n':
        return 1;
    default:
        return 0;
    }
}

int count_words(const char *file_in)
{
    FILE *stream = fopen(file_in, "r");
    if (stream == NULL)
    {
        return -1;
    }
    int nb_mots = 0;
    char c = fgetc(stream);
    if (c == '\n')
    {
        return 0;
    }
    while (c != EOF)
    {
        while (c != EOF && my_issapce(c))
        {
            c = fgetc(stream);
        }
        while (c != EOF && !my_issapce(c))
        {
            c = fgetc(stream);
        }
        nb_mots++;
        c = fgetc(stream);
    }
    return nb_mots;
}

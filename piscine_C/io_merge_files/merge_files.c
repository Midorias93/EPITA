#include <stdio.h>

int my_strlen(char *str)
{
    int compte = 0;
    while (str[compte] != '\0')
    {
        compte++;
    }
    return compte;
}

int merge_files(const char *file_1, const char *file_2)
{
    if (file_1 == NULL || file_2 == NULL)
    {
        return -1;
    }
    FILE *stream1 = fopen(file_2, "r");
    if (stream1 == NULL)
    {
        return -1;
    }
    char buffer[50000];
    char lettre = fgetc(stream1);
    for (int i = 0; lettre != EOF; i++)
    {
        buffer[i] = lettre;
        lettre = fgetc(stream1);
    }
    fclose(stream1);
    FILE *stream3 = fopen(file_1, "r");
    if (stream3 == NULL)
    {
        return -1;
    }
    fclose(stream3);
    int taille_buffer = my_strlen(buffer);
    FILE *stream2 = fopen(file_1, "a");
    if (stream2 == NULL)
    {
        return -1;
    }
    for (int i = 0; i < taille_buffer; i++)
    {
        fputc(buffer[i], stream2);
    }
    fclose(stream2);
    return 0;
}

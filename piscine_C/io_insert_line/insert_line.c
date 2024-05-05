#define _POSIX_C_SOURCE 200809L

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static int nombres_de_ligne(const char *str)
{
    FILE *stream = fopen(str, "r");
    int compte = 0;
    char c = fgetc(stream);
    while (c != EOF)
    {
        if (c == '\n')
        {
            compte++;
        }
        c = fgetc(stream);
    }
    fclose(stream);
    return compte;
}

int insert_line(const char *file_in, const char *file_out, const char *content,
                size_t n)
{
    if (file_in == NULL || file_out == NULL || content == NULL)
    {
        return -1;
    }
    FILE *stream1 = fopen(file_in, "r");
    if (stream1 == NULL)
    {
        return -1;
    }
    FILE *stream2 = fopen(file_out, "w");
    size_t compte = 0;
    int a = 0;
    char c[2];
    c[1] = '\0';
    c[0] = fgetc(stream1);
    while (c[0] != EOF)
    {
        if (a == 0 && compte == n)
        {
            fputs(content, stream2);
            a = 1;
        }
        if (c[0] == '\n')
        {
            compte++;
        }
        fputs(c, stream2);
        c[0] = fgetc(stream1);
    }
    if (a == 0)
    {
        for (size_t i = compte; i < n; i++)
        {
            fputs("\n", stream2);
        }
        fputs(content, stream2);
    }
    fclose(stream1);
    fclose(stream2);
    size_t nb = nombres_de_ligne(file_out);
    return nb > n + 1 ? nb : n + 1;
}

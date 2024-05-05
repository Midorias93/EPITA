#include <stdio.h>

int replace_line(const char *file_in, const char *file_out, const char *content,
                 int n)
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
    char c[2];
    int compte = 0;
    c[1] = '\0';
    c[0] = fgetc(stream1);
    while (c[0] != EOF)
    {
        if (compte == n)
        {
            while (c[0] != EOF && c[0] != '\n')
            {
                c[0] = fgetc(stream1);
            }
            fputs(content, stream2);
            c[0] = c[0] != EOF ? fgetc(stream1) : c[0];
            compte++;
        }
        if (c[0] == '\n')
        {
            compte++;
        }
        if (c[0] != EOF)
        {
            fputs(c, stream2);
        }
        c[0] = c[0] != EOF ? fgetc(stream1) : c[0];
    }
    fclose(stream1);
    fclose(stream2);
    return 0;
}

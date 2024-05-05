#include <stdio.h>

int reverse_content(const char *file_in, const char *file_out)
{
    if (file_in == NULL || file_out == NULL)
    {
        return -1;
    }
    FILE *stream1 = fopen(file_in, "r");
    if (stream1 == NULL)
    {
        return -1;
    }
    FILE *stream2 = fopen(file_out, "w");
    int a = fseek(stream1, -1, SEEK_END);
    char c = fgetc(stream1);
    while (a != -1)
    {
        fputc(c, stream2);
        a = fseek(stream1, -2, SEEK_CUR);
        c = fgetc(stream1);
    }
    fclose(stream1);
    fclose(stream2);
    return 0;
}

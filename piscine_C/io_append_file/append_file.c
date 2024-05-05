#include <stdio.h>

int append_file(const char *file_in, const char *content)
{
    if (file_in == NULL || content == NULL)
    {
        return -1;
    }
    FILE *stream = fopen(file_in, "a");
    if (stream == NULL)
    {
        return -1;
    }
    fprintf(stream, "%s", content);
    fclose(stream);
    return 0;
}

#include "string.h"

#include <stdlib.h>
#include <string.h>

struct string *string_create(const char *str, size_t size)
{
    struct string *string = malloc(sizeof(struct string));
    char *str_copy = malloc(sizeof(char) * size);
    for (size_t i = 0; i < size; i++)
    {
        str_copy[i] = str[i];
    }
    string->data = str_copy;
    string->size = size;
    return string;
}

int string_compare_n_str(const struct string *str1, const char *str2, size_t n)
{
    for (size_t i = 0; i < str1->size && i < n; i++)
    {
        if (str1->data[i] != str2[i])
        {
            return str1->data[i] - str2[i];
        }
    }
    return 0;
}

void string_concat_str(struct string *str, const char *to_concat, size_t size)
{
    if (to_concat == NULL)
    {
        return;
    }
    size_t size_tot = str->size + size;
    str->data = realloc(str->data, size_tot);
    for (size_t i = str->size; i < size_tot; i++)
    {
        str->data[i] = to_concat[i - str->size];
    }
    str->size = size_tot;
}

void string_destroy(struct string *str)
{
    free(str->data);
    free(str);
}

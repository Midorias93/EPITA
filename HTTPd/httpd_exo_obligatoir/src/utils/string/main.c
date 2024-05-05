#include <stdio.h>

#include "string.h"

int main(void)
{
    struct string *str = string_create("te\0st", 6);
    printf("%d\n", string_compare_n_str(str, "ts\0caca", 8));
    for (int i = 0; i < 6; i++)
    {
        printf("%c", str->data[i]);
    }
    printf("\n");
    string_concat_str(str, "ajo\0ut", 7);
    for (int i = 0; i < 13; i++)
    {
        printf("%c", str->data[i]);
    }
    printf("\n");
    string_destroy(str);
}

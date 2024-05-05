#include "variant.h"

#include <stddef.h>
#include <stdio.h>

void variant_display(const struct variant *e)
{
    if (e->type == TYPE_INT)
    {
        printf("%d\n", e->value.int_v);
    }
    else if (e->type == TYPE_FLOAT)
    {
        printf("%f\n", e->value.float_v);
    }
    else if (e->type == TYPE_CHAR)
    {
        printf("%c\n", e->value.char_v);
    }
    else
    {
        printf("%s\n", e->value.str_v);
    }
}

int check_alphabet(const char *str, const char *alphabet)
{
    if (alphabet == NULL || *alphabet == '\0')
    {
        return 1;
    }
    int i = 0;
    int j = 0;
    while (alphabet[i] != '\0')
    {
        j = 0;
        while (str[j] != '\0')
        {
            if (str[j] == alphabet[i])
            {
                break;
            }
            j++;
        }
        i++;
        if (str[j] != '\0')
        {
            continue;
        }
        return 0;
    }
    return 1;
}

bool variant_equal(const struct variant *left, const struct variant *right)
{
    if (left == NULL && right == NULL)
    {
        return 1;
    }
    if (left == NULL || right == NULL)
    {
        return 0;
    }
    if (left->type == right->type && left->type == TYPE_INT
        && left->value.int_v == right->value.int_v)
    {
        return 1;
    }
    else if (left->type == right->type && left->type == TYPE_FLOAT
             && left->value.float_v == right->value.float_v)
    {
        return 1;
    }
    else if (left->type == right->type && left->type == TYPE_CHAR
             && left->value.char_v == right->value.char_v)
    {
        return 1;
    }
    else if (left->type == right->type && left->type == TYPE_STRING
             && check_alphabet(left->value.str_v, right->value.str_v))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int variant_find(const struct variant *array, size_t len, enum type type,
                 union type_any value)
{
    const struct variant tmp = {
        .type = type,
        .value = value,
    };
    for (size_t i = 0; i < len; i++)
    {
        if (variant_equal(&(array[i]), &tmp))
        {
            return i;
        }
    }
    return -1;
}

float variant_sum(const struct variant *array, size_t len)
{
    float compte = 0;
    for (size_t i = 0; i < len; i++)
    {
        if (array[i].type == TYPE_INT || array[i].type == TYPE_FLOAT)
        {
            if (array[i].type == TYPE_INT)
            {
                compte += array[i].value.int_v;
            }
            else
            {
                compte += array[i].value.float_v;
            }
        }
    }
    return compte;
}

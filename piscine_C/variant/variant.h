#ifndef VARIANT_H
#define VARIANT_H

#include <stdbool.h>
#include <stddef.h>

enum type
{
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_CHAR,
    TYPE_STRING
};

union type_any
{
    int int_v;
    float float_v;
    char char_v;
    const char *str_v;
};

struct variant
{
    enum type type;
    union type_any value;
};

void variant_display(const struct variant *e);
bool variant_equal(const struct variant *left, const struct variant *right);
int variant_find(const struct variant *array, size_t len, enum type type,
                 union type_any value);
float variant_sum(const struct variant *array, size_t len);

#endif /* !VARIANT_H */

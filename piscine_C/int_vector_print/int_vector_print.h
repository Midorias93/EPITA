#ifndef INT_VECTOR_PRINT_H
#define INT_VECTOR_PRINT_H

#define INT_VECTOR_LENGTH 64

#include <stddef.h>

struct int_vector
{
    size_t size;
    int data[INT_VECTOR_LENGTH];
};

void int_vector_print(const struct int_vector vec);

#endif /* !INT_VECTOR_PRINT_H */

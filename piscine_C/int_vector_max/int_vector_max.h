#ifndef INT_VECTOR_MAX_H
#define INT_VECTOR_MAX_H

#include <stddef.h>

#define INT_VECTOR_LENGTH 64

struct int_vector
{
    size_t size;
    int data[INT_VECTOR_LENGTH];
};

int int_vector_max(const struct int_vector vec);

#endif /* !INT_VECTOR_MAX_H */

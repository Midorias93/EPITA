#ifndef INT_VECTOR_VICE_MAX_H
#define INT_VECTOR_VICE_MAX_H

#define INT_VECTOR_LENGTH 64

#include <stddef.h>

struct int_vector
{
    size_t size;
    int data[INT_VECTOR_LENGTH];
};

int int_vector_vice_max(const struct int_vector vec);

#endif /* !INT_VECTOR_VICE_MAX_H */

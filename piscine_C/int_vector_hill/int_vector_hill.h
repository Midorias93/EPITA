#ifndef INT_VECTOR_HILL_H
#define INT_VECTOR_HILL_H

#include <stddef.h>

#define INT_VECTOR_LENGTH 64

struct int_vector
{
    size_t size;
    int data[INT_VECTOR_LENGTH];
};

int int_vector_hill(struct int_vector vec);

#endif /* !INT_VECTOR_HILL_H */

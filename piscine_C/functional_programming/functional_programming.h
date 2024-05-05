#ifndef FUNCTIONAL_PROGRAMMING_H
#define FUNCTIONAL_PROGRAMMING_H

#include <stddef.h>

void map(int *array, size_t len, void (*func)(int *));
int foldr(int *array, size_t len, int (*func)(int, int));
int foldl(int *array, size_t len, int (*func)(int, int));

#endif /* !FUNCTIONAL_PROGRAMMING_H */

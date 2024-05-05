#ifndef MALLOC_H
#define MALLOC_H

#include <stddef.h>

struct meta *page_creator(size_t size);
struct block *find_free_block(struct meta *meta, size_t size);
void *my_malloc(size_t size);
void my_free(void *ptr);
void *my_realloc(void *ptr, size_t size);

#endif // MALLOC_H

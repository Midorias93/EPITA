#ifndef STRUCT_H
#define STRUCT_H

#include <stddef.h>

struct block
{
    size_t size;
    size_t size_tot;
    int is_allocated;
    struct block *prev;
    struct block *next;
};

struct meta
{
    struct meta *prev;
    struct meta *next;
    size_t empty_size;
    size_t size;
    struct block *block;
};

struct block *init_block(size_t size, void *ptr);
void *allocate_block(struct block *block, size_t size, int *a);
void free_block(struct block *block, struct meta *meta);
void resize_block(struct block *block, size_t new_size);

struct meta *init_meta(void *ptr, size_t empty_size);
void resize_meta(struct meta *meta, size_t new_size);
struct meta *delet_meta(struct meta *meta, struct meta **first_meta);
void link_page(struct meta *meta1, struct meta *meta2);

#endif // STRUCT_H

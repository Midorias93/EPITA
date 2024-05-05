#include "alignment.h"
#include "struct.h"

struct block *init_block(size_t size, void *ptr)
{
    struct block *block = ptr;
    block->size_tot = align(size) + align(sizeof(struct block));
    block->size = align(size);
    block->is_allocated = 0;
    block->prev = NULL;
    block->next = NULL;
    return block;
}

void resize_block(struct block *block, size_t new_size)
{
    block->size_tot = block->size_tot - block->size + new_size;
    block->size = new_size;
}

void *allocate_block(struct block *block_free, size_t size, int *a)
{
    if (block_free->size == size
        || block_free->size - align(size) <= sizeof(struct block))
    {
        block_free->is_allocated = 1;
        return deplace_ptr(block_free, align(sizeof(struct block)));
    }
    else
    {
        *a = 1;
        block_free->is_allocated = 1;
        size_t size_new_block =
            block_free->size - align(size) - align(sizeof(struct block));
        resize_block(block_free, align(size));
        char *tmp = (void *)block_free;
        tmp = tmp + block_free->size_tot;
        void *ptr = tmp;
        struct block *new_block = init_block(size_new_block, ptr);
        new_block->prev = block_free;
        new_block->next = block_free->next;
        block_free->next = new_block;
        return deplace_ptr(block_free, align(sizeof(struct block)));
    }
}

void free_block(struct block *block, struct meta *meta)
{
    meta->empty_size += block->size;
    while (block->next != NULL && block->next->is_allocated == 0)
    {
        meta->empty_size += align(sizeof(struct block));
        resize_block(block, block->size + block->next->size_tot);
        block->next = block->next->next;
    }
    while (block->prev != NULL && block->prev->is_allocated == 0)
    {
        meta->empty_size += align(sizeof(struct block));
        resize_block(block->prev, block->size + block->prev->size_tot);
        block->prev->next = block->next;
        if (block->next != NULL)
        {
            block->next->prev = block->prev;
        }
        block = block->prev;
    }
    block->is_allocated = 0;
}

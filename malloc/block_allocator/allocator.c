#include "allocator.h"

#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

struct blk_allocator *blka_new(void)
{
    {
        struct blk_allocator *blka = malloc(sizeof(struct blk_allocator));
        if (blka == NULL)
        {
            return NULL;
        }
        blka->meta = NULL;
        return blka;
    }
}

struct blk_meta *blka_alloc(struct blk_allocator *blka, size_t size)
{
    size_t page_size = sysconf(_SC_PAGESIZE);
    size_t total_size = size + sizeof(struct blk_meta);
    size_t nb_pages = (total_size + page_size - 1) / page_size;
    struct blk_meta *new_meta =
        mmap(NULL, nb_pages * page_size, PROT_READ | PROT_WRITE,
             MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (new_meta == MAP_FAILED)
    {
        return NULL;
    }
    new_meta->size = nb_pages * page_size - sizeof(struct blk_meta);
    new_meta->next = blka->meta;
    blka->meta = new_meta;
    return new_meta;
}

void blka_free(struct blk_meta *blk)
{
    munmap(blk, blk->size + sizeof(struct blk_meta));
}

void blka_pop(struct blk_allocator *blka)
{
    if (blka->meta == NULL)
    {
        return;
    }
    struct blk_meta *save = blka->meta;
    blka->meta = save->next;
    blka_free(save);
}

void blka_delete(struct blk_allocator *blka)
{
    while (blka->meta != NULL)
    {
        blka_pop(blka);
    }
    free(blka);
}

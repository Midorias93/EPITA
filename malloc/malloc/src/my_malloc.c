#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

#include "alignment.h"
#include "malloc.h"
#include "struct.h"

struct meta *first_page = NULL;

struct meta *page_creator(size_t size)
{
    size_t page_size = sysconf(_SC_PAGESIZE);
    size_t total_size =
        align(size) + align(sizeof(struct block)) + align(sizeof(struct meta));
    size_t nb_pages = (total_size + page_size - 1) / page_size;
    void *ptr = mmap(NULL, nb_pages * page_size, PROT_READ | PROT_WRITE,
                     MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (ptr == MAP_FAILED)
    {
        return NULL;
    }
    struct meta *meta =
        init_meta(ptr,
                  nb_pages * page_size - align(sizeof(struct block))
                      - align(sizeof(struct meta)));
    meta->block = init_block(meta->empty_size,
                             deplace_ptr(ptr, align(sizeof(struct meta))));
    return meta;
}

static struct meta *ajout_page(struct meta *meta, size_t size)
{
    struct meta *resultat = meta;
    while (resultat->next != NULL)
    {
        resultat = resultat->next;
    }
    link_page(resultat, page_creator(size));
    return resultat->next;
}

struct block *allocate_free_block(struct meta *meta, size_t size)
{
    struct meta *save = meta;
    int a = 0;
    while (save != NULL)
    {
        if (save->empty_size >= size)
        {
            struct block *block = save->block;
            while (block->next != NULL
                   && (block->is_allocated == 1 || block->size < size))
            {
                block = block->next;
            }
            if (block->size >= size)
            {
                void *resultat = allocate_block(block, size, &a);
                a == 1 ? resize_meta(save, save->empty_size - block->size_tot)
                       : resize_meta(save, save->empty_size - block->size);
                return resultat;
            }
        }
        save = save->next;
    }
    struct meta *new_page = ajout_page(first_page, size);
    void *resultat = allocate_block(new_page->block, size, &a);
    a == 1
        ? resize_meta(new_page,
                      new_page->empty_size - new_page->block->size_tot)
        : resize_meta(new_page, new_page->empty_size - new_page->block->size);
    return resultat;
}

void *my_malloc(size_t size)
{
    if (first_page == NULL)
    {
        first_page = page_creator(size);
    }
    return allocate_free_block(first_page, size);
}

static struct meta *trouve_page(struct block *block)
{
    struct block *save = block;
    while (save->prev != NULL)
    {
        save = save->prev;
    }
    return deplace_ptr(save, -align(sizeof(struct meta)));
}

void my_free(void *ptr)
{
    struct block *block = deplace_ptr(ptr, -align(sizeof(struct block)));
    struct meta *debut_page = trouve_page(block);
    free_block(block, debut_page);
    if (debut_page->size == debut_page->empty_size)
    {
        munmap(delet_meta(debut_page, &first_page),
               debut_page->size + align(sizeof(struct meta))
                   + align(sizeof(struct block)));
    }
}

void *my_realloc(void *ptr, size_t size)
{
    struct block *block = deplace_ptr(ptr, -align(sizeof(struct block)));
    if (block->size > size)
    {
        return ptr;
    }
    else
    {
        void *res = memcpy(my_malloc(size), ptr, block->size);
        my_free(ptr);
        return res;
    }
}

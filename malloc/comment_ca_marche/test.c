#include <stdio.h>
#include <sys/mman.h>

static void deplace_ptr(void *ptr, size_t deplacement)
{
    char *deplace = ptr;
    deplace = deplace + deplacement;
    ptr = deplace;
}

int main(void)
{
    struct block
    {
        size_t size;
        int is_allocated;
    };
    struct block block = {
        .size = 20,
        .is_allocated = 1,
    };
    void *test = mmap(NULL, 1, PROT_READ | PROT_WRITE,
                      MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    struct block *save = test;
    deplace_ptr(save, 32);
    *save = block;
    struct block *block_save = test;
    block_save = block_save + 32;
    printf("%ld\n", block_save->size);
    munmap(test, 1);
}

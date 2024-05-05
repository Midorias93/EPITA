#include "page_begin.h"

#include <stddef.h>

void *page_begin(void *ptr, size_t page_size)
{
    char *char_ptr = ptr;
    char_ptr = char_ptr - ((size_t)ptr & (page_size - 1));
    return char_ptr;
}

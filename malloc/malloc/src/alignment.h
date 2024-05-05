#ifndef ALIGNMENT_H
#define ALIGNMENT_H

#define _GNU_SOURCE

#include <stddef.h>

size_t align(size_t size);
void *deplace_ptr(void *ptr, int deplacement);
void *page_begin(void *ptr, size_t page_size);

#endif /* !ALIGNMENT_H */

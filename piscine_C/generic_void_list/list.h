#ifndef LIST_H
#define LIST_H

#include <stddef.h>

struct list
{
    void *data;
    struct list *next;
};

/*
** Insert a node containing `value` at the beginning of the list.
** Return `NULL` if an error occurred.
*/
struct list *list_prepend(struct list *list, const void *value,
                          size_t data_size);

/*
** Return the length of the list.
** Return `0` if the list is empty.
*/
size_t list_length(struct list *list);

/*
** Release the memory used by the list.
** Does nothing if `list` is `NULL`.
*/
void list_destroy(struct list *list);

#endif /* !LIST_H */

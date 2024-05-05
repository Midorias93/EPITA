#ifndef BST_STATIC_H
#define BST_STATIC_H

#include <stddef.h>

struct value
{
    int val;
};

struct bst
{
    size_t capacity;
    size_t size;
    struct value **data;
};

struct bst *init(size_t capacity);
void add(struct bst *tree, int value);
int search(struct bst *tree, int value);
void bst_free(struct bst *tree);

#endif /* !BST_STATIC_H */

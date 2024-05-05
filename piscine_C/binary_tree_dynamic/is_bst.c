#include <limits.h>
#include <stddef.h>
#include <stdio.h>

#include "binary_tree.h"

int aux_bst(const struct binary_tree *tree, int min, int max)
{
    if (tree == NULL)
    {
        return 1;
    }
    if (tree->data < min || tree->data >= max)
    {
        return 0;
    }
    return aux_bst(tree->left, min, tree->data)
        && aux_bst(tree->right, tree->data, max);
}

int is_bst(const struct binary_tree *tree)
{
    int min = INT_MIN;
    int max = INT_MAX;
    return aux_bst(tree, min, max);
}

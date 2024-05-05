#include <stddef.h>

#include "binary_tree.h"

int size(const struct binary_tree *tree)
{
    if (tree == NULL)
    {
        return 0;
    }
    return 1 + size(tree->left) + size(tree->right);
}

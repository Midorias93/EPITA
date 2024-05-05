#include <stddef.h>

#include "binary_tree.h"

int height(const struct binary_tree *tree)
{
    if (tree == NULL)
    {
        return -1;
    }
    return 1
        + (height(tree->left) < height(tree->right) ? height(tree->right)
                                                    : height(tree->left));
}

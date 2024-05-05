#include <stddef.h>

#include "binary_tree.h"

int is_full(const struct binary_tree *tree)
{
    if (tree == NULL)
    {
        return 1;
    }
    if ((tree->left == NULL && tree->right != NULL)
        || (tree->right == NULL && tree->left != NULL))
    {
        return 0;
    }
    return is_full(tree->left) && is_full(tree->right);
}

#include "binary_tree.h"

int is_degenerate(const struct binary_tree *tree)
{
    if (height(tree) + 1 == size(tree))
    {
        return 1;
    }
    return 0;
}

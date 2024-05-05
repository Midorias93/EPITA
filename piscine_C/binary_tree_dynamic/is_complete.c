#include <stddef.h>

#include "binary_tree.h"

static int aux_complete(const struct binary_tree *tree, int nb_noeuds,
                        int index)
{
    if (tree == NULL)
    {
        return 1;
    }
    if (nb_noeuds <= index)
    {
        return 0;
    }
    return aux_complete(tree->left, nb_noeuds, index * 2 + 1)
        && aux_complete(tree->right, nb_noeuds, index * 2 + 2);
}

int is_complete(const struct binary_tree *tree)
{
    return aux_complete(tree, size(tree), 0);
}

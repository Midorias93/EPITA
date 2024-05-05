#include <stddef.h>
#include <stdio.h>

#include "binary_tree.h"

static int aux_perfect(const struct binary_tree *tree, int hauteur_tot,
                       int level)
{
    if (tree == NULL)
    {
        return 1;
    }
    if (tree->left == NULL && tree->right == NULL)
    {
        return hauteur_tot == level;
    }
    if (tree->left == NULL || tree->right == NULL)
    {
        return 0;
    }
    return aux_perfect(tree->left, hauteur_tot, level + 1)
        && aux_perfect(tree->right, hauteur_tot, level + 1);
}

int is_perfect(const struct binary_tree *tree)
{
    return aux_perfect(tree, height(tree), 0);
}

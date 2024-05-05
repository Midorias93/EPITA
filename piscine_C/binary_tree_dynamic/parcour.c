#include <stdio.h>

#include "binary_tree.h"

void dfs_print_prefix(const struct binary_tree *tree)
{
    if (tree == NULL)
    {
        return;
    }
    printf("%d ", tree->data);
    dfs_print_prefix(tree->left);
    dfs_print_prefix(tree->right);
}

void dfs_print_infix(const struct binary_tree *tree)
{
    if (tree == NULL)
    {
        return;
    }
    dfs_print_infix(tree->left);
    printf("%d ", tree->data);
    dfs_print_infix(tree->right);
}

void dfs_print_postfix(const struct binary_tree *tree)
{
    if (tree == NULL)
    {
        return;
    }
    dfs_print_postfix(tree->left);
    dfs_print_postfix(tree->right);
    printf("%d ", tree->data);
}

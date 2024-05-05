#ifndef BINARY_TREE_H
#define BINARY_TREE_H

struct binary_tree
{
    int data;
    struct binary_tree *left;
    struct binary_tree *right;
};

int size(const struct binary_tree *tree);
int height(const struct binary_tree *tree);
void dfs_print_prefix(const struct binary_tree *tree);
void dfs_print_infix(const struct binary_tree *tree);
void dfs_print_postfix(const struct binary_tree *tree);
int is_perfect(const struct binary_tree *tree);
int is_complete(const struct binary_tree *tree);
int is_degenerate(const struct binary_tree *tree);
int is_full(const struct binary_tree *tree);
int is_bst(const struct binary_tree *tree);

#endif /* !BINARY_TREE_H */

#ifndef BST_H
#define BST_H

struct bst_node
{
    int data;
    struct bst_node *left;
    struct bst_node *right;
};

struct bst_node *create_node(int value);
struct bst_node *add_node(struct bst_node *tree, int value);
struct bst_node *delete_node(struct bst_node *tree, int value);
const struct bst_node *find(const struct bst_node *tree, int value);
void free_bst(struct bst_node *tree);

#endif /* !BST_H */

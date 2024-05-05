#include "bst.h"

#include <stdio.h>
#include <stdlib.h>

struct bst_node *create_node(int value)
{
    struct bst_node *new_bst = malloc(sizeof(struct bst_node));
    new_bst->data = value;
    new_bst->left = NULL;
    new_bst->right = NULL;
    return new_bst;
}

struct bst_node *add_node(struct bst_node *tree, int value)
{
    if (tree == NULL)
    {
        struct bst_node *ajout = create_node(value);
        return ajout;
    }
    else
    {
        if (value <= tree->data)
        {
            if (tree->left == NULL)
            {
                struct bst_node *ajout = create_node(value);
                tree->left = ajout;
            }
            else
            {
                add_node(tree->left, value);
            }
        }
        if (value > tree->data)
        {
            if (tree->right == NULL)
            {
                struct bst_node *ajout = create_node(value);
                tree->right = ajout;
            }
            else
            {
                add_node(tree->right, value);
            }
        }
    }
    return tree;
}

static struct bst_node *fait(struct bst_node *tree)
{
    struct bst_node *parent_remplace = tree->left;
    struct bst_node *remplace = parent_remplace->right;
    if (remplace != NULL)
    {
        while (remplace->right != NULL)
        {
            parent_remplace = remplace;
            remplace = remplace->right;
        }
        int sauve = remplace->data;
        parent_remplace->right = remplace->left != NULL ? remplace->left : NULL;
        free(remplace);
        tree->data = sauve;
    }
    else
    {
        int sauve = tree->left->data;
        struct bst_node *gauche = tree->left->left;
        free(tree->left);
        tree->left = gauche;
        tree->data = sauve;
    }
    return tree;
}

struct bst_node *delete_node(struct bst_node *tree, int value)
{
    if (tree == NULL)
    {
        return tree;
    }
    if (tree->data > value)
    {
        tree->left = delete_node(tree->left, value);
        return tree;
    }
    else if (tree->data < value)
    {
        tree->right = delete_node(tree->right, value);
        return tree;
    }
    if (tree->left == NULL && tree->right == NULL)
    {
        free(tree);
        return NULL;
    }
    else if (tree->left == NULL)
    {
        struct bst_node *save = tree->right;
        free(tree);
        return save;
    }
    else if (tree->right == NULL)
    {
        struct bst_node *save = tree->left;
        free(tree);
        return save;
    }
    else
    {
        return fait(tree);
    }
}

const struct bst_node *find(const struct bst_node *tree, int value)
{
    if (tree == NULL)
    {
        return NULL;
    }
    if (tree->data == value)
    {
        return tree;
    }
    if (value > tree->data)
    {
        return find(tree->right, value);
    }
    else if (value <= tree->data)
    {
        return find(tree->left, value);
    }
    return NULL;
}

void free_bst(struct bst_node *tree)
{
    if (tree == NULL)
    {
        return;
    }
    free_bst(tree->left);
    free_bst(tree->right);
    free(tree);
}

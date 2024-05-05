#include "bst_static.h"

#include <stdlib.h>

struct bst *init(size_t capacity)
{
    struct bst *new_b = malloc(sizeof(struct bst));
    new_b->capacity = capacity;
    new_b->size = 0;
    struct value **new_list = malloc(sizeof(struct value *) * capacity);
    for (size_t i = 0; i < capacity; i++)
    {
        new_list[i] = NULL;
    }
    new_b->data = new_list;
    return new_b;
}

static struct bst *resize(struct bst *tree, int capacity)
{
    int save = tree->capacity;
    tree->capacity = capacity;
    tree->data = realloc(tree->data, sizeof(struct value *) * capacity);
    for (size_t i = save; i < tree->capacity; i++)
    {
        tree->data[i] = NULL;
    }
    return tree;
}

static struct value *init_value(int value)
{
    struct value *new_value = malloc(sizeof(struct value));
    new_value->val = value;
    return new_value;
}

static void aux_add(struct bst *tree, int value, size_t i)
{
    if (i >= tree->capacity)
    {
        tree = resize(tree, i + 1);
    }
    if (tree->data[i] == NULL)
    {
        tree->size++;
        tree->data[i] = init_value(value);
        return;
    }
    if (value < tree->data[i]->val)
    {
        aux_add(tree, value, i * 2 + 1);
    }
    if (value > tree->data[i]->val)
    {
        aux_add(tree, value, i * 2 + 2);
    }
}

void add(struct bst *tree, int value)
{
    aux_add(tree, value, 0);
}

static int aux_search(struct bst *tree, int value, int i)
{
    if (tree == NULL)
    {
        return -1;
    }
    if (tree->data[i] == NULL)
    {
        return -1;
    }
    if (tree->data[i]->val == value)
    {
        return i;
    }
    if (tree->data[i]->val >= value)
    {
        return aux_search(tree, value, i * 2 + 1);
    }
    if (tree->data[i]->val < value)
    {
        return aux_search(tree, value, i * 2 + 2);
    }
    return -1;
}

int search(struct bst *tree, int value)
{
    return aux_search(tree, value, 0);
}

void bst_free(struct bst *tree)
{
    for (size_t i = 0; i < tree->size; i++)
    {
        if (tree->data[i] != NULL)
        {
            free(tree->data[i]);
        }
    }
    free(tree->data);
    free(tree);
}

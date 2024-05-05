#include <stdio.h>
#include <stdlib.h>

#include "bst.h"
#include "bst_static.h"

void dfs_print_infix(const struct bst_node *tree)
{
    if (tree == NULL)
    {
        return;
    }
    dfs_print_infix(tree->left);
    printf("%d ", tree->data);
    dfs_print_infix(tree->right);
}

int main(void)
{
    struct bst *bs = init(1);
    for (int i = 0; i < 20; i++)
    {
        add(bs, i);
    }
    for (size_t i = 0; i < bs->capacity; i++)
    {
        if (bs->data[i] != NULL)
        {
            printf("%d\n index: %ld\n", bs->data[i]->val, i);
        }
    }
    bst_free(bs);
}

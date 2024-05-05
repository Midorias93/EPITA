#include "action.h"

#include <stdio.h>

int print(struct token *token, char *path)
{
    if (token == NULL)
    {
        return 0;
    }
    printf("%s\n", path);
    return 1;
}

int delete(struct token *token, char *path)
{
    if (token == NULL)
    {
        return 0;
    }
    int result = remove(path);
    if (result == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

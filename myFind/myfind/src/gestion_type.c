#include <string.h>

#include "my_find.h"

int donne_type(char *type)
{
    if (strcmp(type, "-print") == 0)
    {
        return PRINT;
    }
    else if (strcmp(type, "-delete") == 0)
    {
        return DELETE;
    }
    else if (strcmp(type, "-execdir") == 0)
    {
        return EXECDIR;
    }
    else if (strcmp(type, "-exec") == 0)
    {
        return EXEC;
    }
    else if (strcmp(type, "-name") == 0)
    {
        return NAME;
    }
    else if (strcmp(type, "-type") == 0)
    {
        return TYPE;
    }
    else if (strcmp(type, "-o") == 0)
    {
        return OR;
    }
    else if (strcmp(type, "-a") == 0)
    {
        return AND;
    }
    else if (strcmp(type, "-newer") == 0)
    {
        return NEWER;
    }
    else if (strcmp(type, "-user") == 0)
    {
        return USER;
    }
    else if (strcmp(type, "-group") == 0)
    {
        return GROUP;
    }
    else if (strcmp(type, "(") == 0)
    {
        return P_G;
    }
    else if (strcmp(type, ")") == 0)
    {
        return P_D;
    }
    else if (strcmp(type, "!") == 0)
    {
        return P_EXCLA;
    }
    else
    {
        return -1;
    }
}

int possed_un_argument(int type)
{
    switch (type)
    {
    case PRINT:
        return 0;
    case DELETE:
        return 0;
    case NAME:
        return 1;
    case TYPE:
        return 1;
    case USER:
        return 1;
    case GROUP:
        return 1;
    case OR:
        return 0;
    case AND:
        return 0;
    case NEWER:
        return 1;
    case PERM:
        return 1;
    case P_G:
        return 0;
    case P_D:
        return 0;
    case P_EXCLA:
        return 0;
    default:
        return 0;
    }
}

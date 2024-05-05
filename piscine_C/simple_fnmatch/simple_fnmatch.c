#include "simple_fnmatch.h"

int simple_fnmatch(const char *pattern, const char *string)
{
    int a = 0;
    int b = 0;
    int c = 0;
    if (pattern[0] == '\0')
    {
        if (string[0] == '\0')
        {
            return 0;
        }
        return FNM_NOMATCH;
    }
    else if (string[0] == '\0')
    {
        if (pattern[0] == '*' && pattern[1] == '\0')
        {
            return 0;
        }
        return FNM_NOMATCH;
    }
    else
    {
        switch (pattern[0])
        {
        case '?':
            return simple_fnmatch(pattern + 1, string + 1);
        case '\\':
            if (string[0] == pattern[1])
                return simple_fnmatch(pattern + 2, string + 1);
            return FNM_NOMATCH;
        case '*':
            a = simple_fnmatch(pattern + 1, string);
            b = simple_fnmatch(pattern, string + 1);
            c = simple_fnmatch(pattern + 1, string + 1);
            return a && b && c;
        default:
            if (pattern[0] == string[0])
                return simple_fnmatch(pattern + 1, string + 1);
            return FNM_NOMATCH;
        }
    }
}

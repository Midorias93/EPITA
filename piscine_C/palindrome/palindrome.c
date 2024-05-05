#include <stdio.h>

int test_min(char c)
{
    if (c >= 'a' && c <= 'z')
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
int test_maj(char c)
{
    if (c >= 'A' && c <= 'Z')
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int test_num(char c)
{
    if (c >= '0' && c <= '9')
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int palindrome(const char *s)
{
    if (s == NULL)
    {
        return 0;
    }
    int t = 0;
    while (s[t] != '\0')
    {
        t++;
    }
    t--;
    int i = 0;
    while (i < t)
    {
        while (test_maj(s[i]) + test_num(s[i]) + test_min(s[i]) == 3)
        {
            i++;
        }
        while (test_maj(s[t]) + test_num(s[t]) + test_min(s[t]) == 3)
        {
            t--;
        }
        if (s[t] != s[i])
        {
            return 0;
        }
        t--;
        i++;
    }
    return 1;
}

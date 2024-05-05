#include <stddef.h>

size_t max(size_t a, size_t b)
{
    size_t max = a;
    max = (max < b) ? b : max;
    return max;
}

size_t min3(size_t a, size_t b, size_t c)
{
    size_t min = a;
    min = (min > b) ? b : min;
    min = (min > c) ? c : min;
    return min;
}

size_t min2(size_t a, size_t b)
{
    size_t min = a;
    min = (min > b) ? b : min;
    return min;
}

size_t str_len(const char *str)
{
    size_t taille = 0;
    while (str[taille] != '\0')
    {
        taille++;
    }
    return taille;
}

size_t levenshtein(const char *s1, const char *s2)
{
    if (min2(str_len(s1), str_len(s2)) == 0)
    {
        return max(str_len(s1), str_len(s2));
    }
    else if (s1[0] == s2[0])
    {
        return levenshtein(s1 + 1, s2 + 1);
    }
    else
    {
        return 1
            + min3(levenshtein(s1 + 1, s2), levenshtein(s1, s2 + 1),
                   levenshtein(s1 + 1, s2 + 1));
    }
}

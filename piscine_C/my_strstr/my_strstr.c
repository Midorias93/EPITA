int my_strstr(const char *haystack, const char *needle)
{
    if (*haystack == '\0' && *needle == '\0')
    {
        return 0;
    }
    int i = 0;
    int k = 0;
    int retenu = 0;
    while (haystack[i] != '\0')
    {
        retenu = i;
        while (needle[k] == haystack[i] && haystack[i] != '\0')
        {
            i++;
            k++;
        }
        if (needle[k] == '\0')
        {
            return retenu;
        }
        else
        {
            i = retenu;
            k = 0;
            i++;
        }
    }
    return -1;
}

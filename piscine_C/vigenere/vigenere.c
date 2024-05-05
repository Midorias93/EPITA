static void struppercase(const char *entre, char *sortie)
{
    int i = 0;
    while (entre[i] != '\0')
    {
        if (entre[i] >= 'a' && entre[i] <= 'z')
        {
            sortie[i] = entre[i] - 32;
        }
        else
        {
            sortie[i] = entre[i];
        }
        i++;
    }
}

static int len(const char *str)
{
    int len = 0;
    while (str[len] != '\0')
    {
        len++;
    }
    return len;
}

static int notalpha(char c)
{
    if (c >= 'A' && c <= 'Z')
    {
        return 0;
    }
    return 1;
}

void cipher(const char *key, const char *msg, char *res)
{
    int i = 0;
    int j = 0;
    int val_key = 0;
    int len_key = len(key);
    struppercase(msg, res);
    while (res[i] != '\0')
    {
        if (notalpha(res[i]))
        {
            i++;
            continue;
        }
        val_key = key[j];
        if (val_key >= 'a' && val_key <= 'z')
        {
            val_key -= 32;
        }
        res[i] = (res[i] - 'A' + val_key - 'A') % 26 + 'A';
        i++;
        j = (j + 1) % len_key;
    }
}

void decipher(const char *key, const char *msg, char *res)
{
    int i = 0;
    int j = 0;
    int val_key = 0;
    int len_key = len(key);
    struppercase(msg, res);
    while (res[i] != '\0')
    {
        if (notalpha(res[i]))
        {
            i++;
            continue;
        }
        val_key = key[j];
        if (val_key >= 'a' && val_key <= 'z')
        {
            val_key -= 32;
        }
        res[i] = ((res[i] - 'A') - (val_key - 'A') + 26) % 26 + 'A';
        i++;
        j = (j + 1) % len_key;
    }
}

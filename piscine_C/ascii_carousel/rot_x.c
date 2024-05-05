#include <stddef.h>

int modulo(int debut, int fin, int nombre, int ajout)
{
    if (ajout < 0)
    {
        if (nombre + ajout < debut)
        {
            ajout += nombre - debut;
            fin -= -ajout;
            return fin + 1;
        }
    }
    if (nombre + ajout > fin)
    {
        ajout -= fin - nombre;
        debut += ajout;
        return debut - 1;
    }
    else
    {
        return nombre + ajout;
    }
}

void rot_x(char *s, int x)
{
    if (s == NULL)
    {
        return;
    }
    x = x % 26;
    while (*s != '\0')
    {
        if (*s >= 'a' && *s <= 'z')
        {
            *s = modulo('a', 'z', *s, x);
        }
        if (*s >= 'A' && *s <= 'Z')
        {
            *s = modulo('A', 'Z', *s, x);
        }
        s++;
    }
}

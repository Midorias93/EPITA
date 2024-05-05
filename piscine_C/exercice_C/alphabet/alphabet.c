#include <stdio.h>

int main(void)
{
    char lettre = 'a';
    while (lettre < 122)
    {
        putchar(lettre);
        putchar(' ');
        lettre++;
    }
    putchar(lettre);
    putchar('\n');
    return 0;
}

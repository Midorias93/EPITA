#include <stdio.h>
#include <stddef.h>

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
}

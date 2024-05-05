#include <stdio.h>

void affiche(char *s)
{
    int i = 0;
    while (s[i] != 0)
    {
        printf("%c", s[i]);
        i++;
    }
}

int main(int arg1, char *arg2[])
{
    if (arg2[1] == NULL)
    {
        printf("Hello World!\n");
        return 0;
    }
    for (int i = 1; i < arg1; i++)
    {
        printf("Hello ");
        affiche(arg2[i]);
        printf("!\n");
    }
    return 0;
}

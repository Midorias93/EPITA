#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int modulo_26(int n)
{
    if (n > 0)
    {
        return n % 26;
    }
    else
    {
        return (n % 26) + 26;
    }
}

int modulo_10(int n)
{
    if (n > 0)
    {
        return n % 10;
    }
    else
    {
        return (n % 10) + 10;
    }
}

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        return 0;
    }
    unsigned char bufer[3000];
    int b = atoi(argv[1]);
    int a = read(STDIN_FILENO, bufer, 3000);
    if (a < 0)
    {
        return 1;
    }
    for (int i = 0; i < a; i++)
    {
        if (bufer[i] >= 'a' && bufer[i] <= 'z')
        {
            bufer[i] = (bufer[i] - 'a' + modulo_26(b)) % 26 + 'a';
        }
        if (bufer[i] >= 'A' && bufer[i] <= 'Z')
        {
            bufer[i] = (bufer[i] - 'A' + modulo_26(b)) % 26 + 'A';
        }
        if (bufer[i] >= '0' && bufer[i] <= '9')
        {
            bufer[i] = (bufer[i] - '0' + modulo_10(b)) % 10 + '0';
        }
    }
    if (write(STDOUT_FILENO, bufer, a) < 0)
    {
        return 1;
    }
    return 0;
}

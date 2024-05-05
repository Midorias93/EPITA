#include <stdio.h>

int int_sqrt(int n)
{
    if (n < 0)
    {
        return -1;
    }
    int x = 0;
    while ((x * x) < n)
    {
        x++;
    }
    printf("%d", x);
    return x;
}

int main(void)
{
    int_sqrt(100);
}

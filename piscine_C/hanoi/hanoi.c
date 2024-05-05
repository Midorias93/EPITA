#include <stdio.h>

void aux(unsigned n, int D, int A, int I)
{
    if (n != 0)
    {
        aux(n - 1, D, I, A);
        printf("%d->%d\n", D, A);
        aux(n - 1, I, A, D);
    }
}
void hanoi(unsigned n)
{
    aux(n, 1, 3, 2);
}

int main(void)
{
    hanoi(3);
}

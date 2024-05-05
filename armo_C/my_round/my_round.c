#include <stdio.h>
int my_round(float n)
{
    int a = n;
    float b = a;
    if (n - b >= 0.5 || n - b <= -0.5)
    {
        if (a < 0)
        {
            a--;
        }
        else
        {
            a++;
        }
    }
    return a;
}

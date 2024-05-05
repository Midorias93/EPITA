#include <stdio.h>

void prime_factorization(unsigned long n)
{
    unsigned long facto = 2;
    unsigned long expo = 0;
    unsigned long val = n;
    if (n != 0 && n != 1)
    {
        printf("%ld = ", val);
        while (n != 1 && facto * facto < n)
        {
            expo = 0;
            if (val % facto == 0)
            {
                printf("%ld", facto);
                while (val % facto == 0)
                {
                    expo++;
                    val = val / facto;
                }
                printf("^%ld", expo);
                if (val != 1)
                {
                    printf(" * ");
                }
            }
            if (facto == 2)
            {
                facto++;
            }
            else
            {
                facto += 2;
            }
        }
        if (facto * facto > n && val != 1)
        {
            printf("%ld^%d\n", val, 1);
        }
        else
        {
            printf("\n");
        }
    }
}

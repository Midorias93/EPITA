#include "complex.h"

#include <stdio.h>

float my_abs(float n)
{
    if (n < 0)
    {
        return -n;
    }
    else
    {
        return n;
    }
}

int positif(float n)
{
    if (n < 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

void print_complex(struct complex a)
{
    if (positif(a.img))
    {
        printf("complex(%.2f + %.2fi)\n", a.real, a.img);
    }
    else
    {
        printf("complex(%.2f - %.2fi)\n", a.real, my_abs(a.img));
    }
}

struct complex neg_complex(struct complex a)
{
    struct complex z = {
        .real = -a.real,
        .img = -a.img,
    };
    return z;
}

struct complex add_complex(struct complex a, struct complex b)
{
    struct complex z = {
        .real = a.real + b.real,
        .img = a.img + b.img,
    };
    return z;
}

struct complex sub_complex(struct complex a, struct complex b)
{
    struct complex z = {
        .real = a.real - b.real,
        .img = a.img - b.img,
    };
    return z;
}

struct complex mul_complex(struct complex a, struct complex b)
{
    struct complex z = {
        .real = (a.real * b.real) - (a.img * b.img),
        .img = (a.real * b.img) + (a.img * b.real),
    };
    return z;
}

struct complex div_complex(struct complex a, struct complex b)
{
    struct complex z = {
        .real = ((a.real * b.real) + (a.img * b.img))
            / ((b.real * b.real) + (b.img * b.img)),
        .img = ((a.img * b.real) - (a.real * b.img))
            / ((b.real * b.real) + (b.img * b.img)),
    };
    return z;
}

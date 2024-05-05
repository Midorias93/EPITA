#pragma once
#include "is_prime.hh"

constexpr bool is_prime(unsigned int a)
{
    if (a <= 1)
        return false;

    for (unsigned int i = 2; i <= a / 2; i++)
        if (a % i == 0)
            return false;

    return true;
}

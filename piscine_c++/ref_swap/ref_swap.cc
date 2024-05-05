#include "ref_swap.hh"

void ref_swap(int& a, int& b)
{
    int save = a;
    a = b;
    b = save;
}

void ptr_swap(int* a, int* b)
{
    if (a == nullptr || b == nullptr)
        return;
    int save = *a;
    *a = *b;
    *b = save;
}

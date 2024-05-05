#include "closer_to.hh"

#include <iostream>

CloserTo::CloserTo(int i)
    : i_(i)
{}

bool CloserTo::operator()(int a, int b) const
{
    int dist_a = abs(this->i_ - a);
    int dist_b = abs(this->i_ - b);
    if (dist_a == dist_b)
        return a < b;
    return dist_a < dist_b;
}

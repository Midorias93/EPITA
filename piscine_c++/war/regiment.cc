#include "regiment.hh"

#include <iostream>

void Regiment::join_by(Regiment& r)
{
    for (Soldier& s : r.soldats)
    {
        this->soldats.push_back(s);
    }
    r.soldats.clear();
}

size_t Regiment::count() const
{
    return this->soldats.size();
}

void Regiment::add_soldier(Soldier& s)
{
    this->soldats.push_back(s);
}

void Regiment::print_state() const
{
    for (Soldier& s : this->soldats)
    {
        s.print_state();
    }
}

void Regiment::scream() const
{
    for (Soldier& s : this->soldats)
    {
        s.scream();
    }
}

#pragma once
#include <iostream>
#include <vector>

#include "soldier.hh"

class Regiment
{
public:
    std::vector<std::reference_wrapper<Soldier>> soldats;
    void join_by(Regiment& r);
    size_t count() const;
    void add_soldier(Soldier& s);
    void print_state() const;
    void scream() const;
};

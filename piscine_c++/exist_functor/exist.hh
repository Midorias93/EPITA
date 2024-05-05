#pragma once
#include <vector>

template <class T>
class Exist
{
public:
    bool operator()(T val);

private:
    std::vector<T> vect;
};

#include "exist.hxx"

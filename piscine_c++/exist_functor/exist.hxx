#pragma once
#include "exist.hh"

template <class T>
bool Exist<T>::operator()(T val)
{
    for (const T& elem : this->vect)
    {
        if (elem == val)
        {
            return true;
        }
    }
    this->vect.push_back(val);
    return false;
}

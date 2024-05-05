#pragma once
#include "singleton.hh"
template <typename T>
Singleton<T>::~Singleton()
{
    if (value_ != nullptr)
        delete value_;
}

template <typename T>
T& Singleton<T>::instance()
{
    if (value_ == nullptr)
        value_ = new T();
    return *value_;
}
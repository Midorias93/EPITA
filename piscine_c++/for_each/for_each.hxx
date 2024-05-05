#pragma once

template <class InputIt, class UnaryFunction>
constexpr UnaryFunction my_foreach(InputIt first, InputIt last, UnaryFunction f)
{
    for (; first != last; ++first)
        f(*first);

    return f; // implicit move since C++11
}
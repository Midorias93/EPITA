#pragma once

template <class InputIt, class UnaryFunction>
constexpr UnaryFunction my_foreach(InputIt first, InputIt last,
                                   UnaryFunction f);

#include "for_each.hxx"

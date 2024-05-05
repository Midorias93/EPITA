#pragma once

#include <iostream>

template <typename T> std::ostream& operator<<(Contract contract, T& t)
{
  return std::cerr << contract.fileName << ':' << contract.fileLine << ": "
                   << contract.condType << " `" << contract.condText
                   << "' failed.\n"
                   << t;
}

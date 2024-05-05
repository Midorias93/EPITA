/** \file misc/contract.cc
 ** \brief Implementation for contract.hh
 */

#include <cstdlib>
#include <iostream>

#include <misc/contract.hh>

Contract::Contract(const char* condType,
                   const char* condText,
                   const char* fileName,
                   int fileLine)
  : condType(condType)
  , condText(condText)
  , fileName(fileName)
  , fileLine(fileLine)
{}

Contract::~Contract()
{
  std::cerr << '\n';
  abort();
}

void __Terminate(const char* fileName, int fileLine, const char* reason)
{
  std::cerr << fileName << ":" << fileLine << ": Program abortion (" << reason
            << ")\n";
  abort();
}

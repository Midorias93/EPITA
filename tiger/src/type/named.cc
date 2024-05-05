/**
 ** \file type/named.cc
 ** \brief Implementation for type/named.hh.
 */

#include <set>

#include <type/named.hh>
#include <type/visitor.hh>

namespace type
{
  Named::Named(misc::symbol name)
    : name_(name)
    , type_(nullptr)
  {}

  Named::Named(misc::symbol name, const Type* type)
    : name_(name)
    , type_(type)
  {}

  // Inherited functions
  void Named::accept(ConstVisitor& v) const
  {
    // DONE: Some code was deleted here.
  }

  void Named::accept(Visitor& v)
  {
    // DONE: Some code was deleted here.
  }

  bool Named::sound() const
  {
    // DONE: Some code was deleted here (Sound).
  }

  bool Named::compatible_with(const Type& other) const
  {
    // DONE: Some code was deleted here (Special implementation of "compatible_with" for Named).
  }

} // namespace type

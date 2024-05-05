/**
 ** \file ast/object-exp.cc
 ** \brief Implementation of ast::ObjectExp.
 */

#include <ast/object-exp.hh>
#include <ast/visitor.hh>

namespace ast
{
  ObjectExp::ObjectExp(const Location& location, NameTy* type_name)
    : Exp(location)
    , type_name_(type_name)
  {}

  void ObjectExp::accept(ConstVisitor& v) const { v(*this); }

  void ObjectExp::accept(Visitor& v) { v(*this); }
} // namespace ast

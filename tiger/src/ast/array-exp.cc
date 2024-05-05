/**
 ** \file ast/array-exp.cc
 ** \brief Implementation of ast::ArrayExp.
 */

#include <ast/array-exp.hh>
#include <ast/visitor.hh>

namespace ast
{
  ArrayExp::ArrayExp(const Location& location,
                     NameTy* type_name,
                     Exp* size,
                     Exp* init)
    : Exp(location)
    , type_name_(type_name)
    , size_(size)
    , init_(init)
  {}

  ArrayExp::~ArrayExp()
  {
    delete type_name_;
    delete size_;
    delete init_;
  }

  void ArrayExp::accept(ConstVisitor& v) const { v(*this); }

  void ArrayExp::accept(Visitor& v) { v(*this); }
} // namespace ast

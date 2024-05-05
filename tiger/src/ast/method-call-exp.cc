/**
 ** \file ast/method-call-exp.cc
 ** \brief Implementation of ast::MethodCallExp.
 */

#include <ast/method-call-exp.hh>
#include <ast/visitor.hh>

namespace ast
{
  MethodCallExp::MethodCallExp(const Location& location,
                               misc::symbol name,
                               exps_type* args,
                               Var* object)
    : CallExp(location, name, args)
    , object_(object)
  {}

  MethodCallExp::~MethodCallExp() { delete object_; }

  void MethodCallExp::accept(ConstVisitor& v) const { v(*this); }

  void MethodCallExp::accept(Visitor& v) { v(*this); }
} // namespace ast

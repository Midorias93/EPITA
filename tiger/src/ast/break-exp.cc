/**
 ** \file ast/break-exp.cc
 ** \brief Implementation of ast::BreakExp.
 */

#include <ast/break-exp.hh>
#include <ast/visitor.hh>

namespace ast
{
  BreakExp::BreakExp(const Location& location)
    : Exp(location)
  {}

  void BreakExp::accept(ConstVisitor& v) const { v(*this); }

  void BreakExp::accept(Visitor& v) { v(*this); }
} // namespace ast

/**
 ** \file ast/call-exp.cc
 ** \brief Implementation of ast::CallExp.
 */

#include <ast/call-exp.hh>
#include <ast/visitor.hh>
#include <misc/algorithm.hh>

namespace ast
{
  CallExp::CallExp(const Location& location, misc::symbol name, exps_type* args)
    : Exp(location)
    , name_(name)
    , args_(args)
  {}

  CallExp::~CallExp()
  {
    misc::deep_clear(*args_);
    delete args_;
  }

  void CallExp::accept(ConstVisitor& v) const { v(*this); }

  void CallExp::accept(Visitor& v) { v(*this); }

} // namespace ast

/**
 ** \file ast/let-exp.cc
 ** \brief Implementation of ast::LetExp.
 */

#include <ast/let-exp.hh>
#include <ast/visitor.hh>

namespace ast
{
  LetExp::LetExp(const Location& location, ChunkList* chunks, Exp* body)
    : Exp(location)
    , chunks_(chunks)
    , body_(body)
  {}

  LetExp::~LetExp()
  {
    delete chunks_;
    delete body_;
  }

  void LetExp::accept(ConstVisitor& v) const { v(*this); }

  void LetExp::accept(Visitor& v) { v(*this); }
} // namespace ast

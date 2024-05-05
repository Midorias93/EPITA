/**
 ** \file ast/let-exp.hxx
 ** \brief Inline methods of ast::LetExp.
 */

#pragma once

#include <ast/let-exp.hh>

namespace ast
{

  inline const ChunkList& LetExp::chunks_get() const { return *chunks_; }
  inline ChunkList& LetExp::chunks_get() { return *chunks_; }

  inline const Exp& LetExp::body_get() const { return *body_; }
  inline Exp& LetExp::body_get() { return *body_; }

} // namespace ast

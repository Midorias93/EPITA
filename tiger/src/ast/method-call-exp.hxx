/**
 ** \file ast/method-call-exp.hxx
 ** \brief Inline methods of ast::MethodCallExp.
 */

#pragma once

#include <ast/method-call-exp.hh>

namespace ast
{

  inline const Var& MethodCallExp::object_get() const { return *object_; }
  inline Var& MethodCallExp::object_get() { return *object_; }

    inline const MethodDec* MethodCallExp::def_get() const { return def_; }
    inline MethodDec* MethodCallExp::def_get() { return def_; }
    inline void MethodCallExp::def_set(MethodDec* def) { def_ = def; }

} // namespace ast

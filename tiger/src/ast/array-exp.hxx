/**
 ** \file ast/array-exp.hxx
 ** \brief Inline methods of ast::ArrayExp.
 */

#pragma once

#include <ast/array-exp.hh>

namespace ast
{

  inline const NameTy& ArrayExp::type_name_get() const { return *type_name_; }
  inline NameTy& ArrayExp::type_name_get() { return *type_name_; }

  inline const Exp& ArrayExp::size_get() const { return *size_; }
  inline Exp& ArrayExp::size_get() { return *size_; }

  inline const Exp& ArrayExp::init_get() const { return *init_; }
  inline Exp& ArrayExp::init_get() { return *init_; }

} // namespace ast

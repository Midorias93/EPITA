/**
 ** \file ast/field-var.hxx
 ** \brief Inline methods of ast::FieldVar.
 */

#pragma once

#include <ast/field-var.hh>

namespace ast
{

  inline const Var& FieldVar::var_get() const { return *var_; }
  inline Var& FieldVar::var_get() { return *var_; }

  inline misc::symbol FieldVar::name_get() const { return name_; }
  inline void FieldVar::name_set(misc::symbol name) { name_ = name; }

  inline int FieldVar::index_get() const { return index_; }
  inline void FieldVar::index_set(int index) { index_ = index; }

} // namespace ast

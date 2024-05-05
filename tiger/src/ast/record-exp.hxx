/**
 ** \file ast/record-exp.hxx
 ** \brief Inline methods of ast::RecordExp.
 */

#pragma once

#include <ast/record-exp.hh>

namespace ast
{

  inline const NameTy& RecordExp::type_name_get() const { return *type_name_; }
  inline NameTy& RecordExp::type_name_get() { return *type_name_; }

  inline const fieldinits_type& RecordExp::fields_get() const
  {
    return *fields_;
  }
  inline fieldinits_type& RecordExp::fields_get() { return *fields_; }

} // namespace ast

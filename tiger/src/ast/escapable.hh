/**
 ** \file ast/escapable.hh
 ** \brief Declaration of ast::Escapable.
 */

#pragma once

#include <ast/fwd.hh>
#include <escapes/libescapes.hh>
#include <misc/symbol.hh>

namespace ast
{
  /// Escapable.
  class Escapable
  {
    // DONE: Some code was deleted here.

  public:
      bool escape_get() const;
      bool escape_get();
      void  escape_set(bool escape);
      misc::symbol def_function_get() const;
      misc::symbol def_function_get();
      void def_function_set(misc::symbol def_function);

  private:
      bool escape_ = true;
      misc::symbol def_function_;

  };
} // namespace ast
#include <ast/escapable.hxx>

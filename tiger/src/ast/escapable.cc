/**
 ** \file ast/escapable.cc
 ** \brief Implementation of ast::Escapable.
 */

#include <ast/escapable.hh>
#include <ast/visitor.hh>

namespace ast
{
  // DONE: Some code was deleted here.
    void Escapable::escape_set(bool escape) {
       this->escape_ = escape;
    }

    bool Escapable::escape_get() const {
        return this->escape_;
    }
    bool Escapable::escape_get() {
        return this->escape_;
    }

    misc::symbol Escapable::def_function_get() const {
        return def_function_;
    }

    misc::symbol Escapable::def_function_get() {
        return def_function_;
    }

    void Escapable::def_function_set(misc::symbol def_function) {
        def_function_ = def_function;
    }


} // namespace ast

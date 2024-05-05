/**
 ** \file bind/renamer.hxx
 ** \brief Template methods of bind::Renamer.
 */

#pragma once

#include <bind/renamer.hh>
#include <misc/symbol.hh>

namespace bind
{
  template <class E, class Def> void Renamer::visit(E& e, const Def* def)
  {
    if (static_cast<ast::Ast*>(&e) == static_cast<const ast::Ast*>(def) || def == nullptr) {
        auto new_name = misc::symbol::fresh(e.name_get());
        e.name_set(new_name);
    }
    else {
        e.name_set(def->name_get());
    }

  }
} // namespace bind

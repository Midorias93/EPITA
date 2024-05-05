/**
 ** \file object/libobject.hh
 ** \brief Declare functions and variables exported by object module.
 */

#pragma once

#include <ast/fwd.hh>
#include <misc/error.hh>
#include <object/fwd.hh>

namespace object
{
  /*-------.
  | Bind.  |
  `-------*/

  // FIXME: Some code was deleted here.

  /*----------------.
  | Compute types.  |
  `----------------*/

  /** \brief Check types allowing objects.

      \param tree abstract syntax tree's root.

      \return success of the type-checking.  */
  misc::error types_check(ast::Ast& tree);

} // namespace object

#include <object/libobject.hxx>

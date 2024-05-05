/**
 ** \file object/libobject.cc
 ** \brief Define exported object functions.
 */

// FIXME: Some code was deleted here.
#include <object/libobject.hh>
#include <object/type-checker.hh>

namespace object
{
  /*-------.
  | Bind.  |
  `-------*/

  // FIXME: Some code was deleted here.

  /*----------------.
  | Compute types.  |
  `----------------*/

  misc::error types_check(ast::Ast& tree)
  {
    TypeChecker type;
    type(tree);
    return type.error_get();
  }

} // namespace object
